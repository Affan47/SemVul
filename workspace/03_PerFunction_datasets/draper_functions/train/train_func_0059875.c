tag_make_color(TAGSTRING *buf, int maxlen, uint32 color)
{
	if (maxlen <= (signed)sizeof (ht_tag_color)) return tag_error(buf, maxlen);
	ht_tag_color tag;
	tag.escape = '\e';
	tag.magic = HT_TAG_COLOR;
	tag.color = color;
	tag.flush(buf);
	return buf + sizeof(tag);
}
