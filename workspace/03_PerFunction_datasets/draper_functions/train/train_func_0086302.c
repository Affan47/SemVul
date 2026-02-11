append_attribute_uninitialized(QByteArray *buf, quint16 type, int len)
{
	if(len > ATTRIBUTE_VALUE_MAX)
		return -1;

	quint16 alen = (quint16)len;
	quint16 plen = round_up_length(alen);

	if((buf->size() - ATTRIBUTE_AREA_START) + 4 + plen > ATTRIBUTE_AREA_MAX)
		return -1;

	int at = buf->size();
	buf->resize(buf->size() + 4 + plen);
	quint8 *p = (quint8 *)buf->data();

	write16(p + at, type);
	write16(p + at + 2, alen);


	for(int n = 0; n < plen - alen; ++n)
		p[at + alen + n] = 0;

	return at;
}
