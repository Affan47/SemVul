encode_uleb128 (guint32 value, guint8 *buf, guint8 **endbuf)
{
	guint8 *p = buf;

	do {
		guint8 b = value & 0x7f;
		value >>= 7;
		if (value != 0)
			b |= 0x80;
		*p ++ = b;
	} while (value);

	*endbuf = p;
}
