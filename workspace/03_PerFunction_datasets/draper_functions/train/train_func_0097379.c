httpHeaderGetStr(const HttpHeader * hdr, http_hdr_type id)
{
    HttpHeaderEntry *e;
    assert_eid(id);
    assert(Headers[id].type == ftStr);
    if ((e = httpHeaderFindEntry(hdr, id))) {
	httpHeaderNoteParsedEntry(e->id, e->value, 0);
	return strBuf(e->value);
    }
    return NULL;
}
