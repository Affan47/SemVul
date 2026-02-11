flat_read_property(struct inbuf *dtbuf,
					   struct inbuf *strbuf, int flags)
{
	uint32_t proplen, stroff;
	char *name;
	struct data val;

	proplen = flat_read_word(dtbuf);
	stroff = flat_read_word(dtbuf);

	name = flat_read_stringtable(strbuf, stroff);

	if ((flags & FTF_VARALIGN) && (proplen >= 8))
		flat_realign(dtbuf, 8);

	val = flat_read_data(dtbuf, proplen);

	return build_property(name, val);
}
