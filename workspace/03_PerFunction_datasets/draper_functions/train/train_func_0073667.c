httpHeaderEntryParseCreate(const char *field_start, const char *field_end)
{
    HttpHeaderEntry *e;
    int id;

    const char *name_end = memchr(field_start, ':', field_end - field_start);
    int name_len = name_end ? name_end - field_start : 0;
    const char *value_start = field_start + name_len + 1;


    HeaderEntryParsedCount++;


    if (!name_len || name_end > field_end)
	return NULL;
    if (name_len > 65534) {

	debug(55, 1) ("WARNING: ignoring header name of %d bytes\n", name_len);
	return NULL;
    }
    if (Config.onoff.relaxed_header_parser && xisspace(field_start[name_len - 1])) {
	debug(55, Config.onoff.relaxed_header_parser <= 0 ? 1 : 2)
	    ("NOTICE: Whitespace after header name in '%s'\n", getStringPrefix(field_start, field_end));
	while (name_len > 0 && xisspace(field_start[name_len - 1]))
	    name_len--;
	if (!name_len)
	    return NULL;
    }

    e = memAllocate(MEM_HTTP_HDR_ENTRY);
    debug(55, 9) ("creating entry %p: near '%s'\n", e, getStringPrefix(field_start, field_end));

    id = httpHeaderIdByName(field_start, name_len, Headers, HDR_ENUM_END);
    if (id < 0)
	id = HDR_OTHER;
    assert_eid(id);
    e->id = id;

    if (id == HDR_OTHER)
	stringLimitInit(&e->name, field_start, name_len);
    else
	e->name = Headers[id].name;

    while (value_start < field_end && xisspace(*value_start))
	value_start++;
    while (value_start < field_end && xisspace(field_end[-1]))
	field_end--;
    if (field_end - value_start > 65534) {

	debug(55, 1) ("WARNING: ignoring '%s' header of %d bytes\n",
	    strBuf(e->name), (int) (field_end - value_start));
	if (e->id == HDR_OTHER)
	    stringClean(&e->name);
	memFree(e, MEM_HTTP_HDR_ENTRY);
	return NULL;
    }

    stringLimitInit(&e->value, value_start, field_end - value_start);
    Headers[id].stat.seenCount++;
    Headers[id].stat.aliveCount++;
    debug(55, 9) ("created entry %p: '%s: %s'\n", e, strBuf(e->name), strBuf(e->value));
    return e;
}
