write_unsigned_compress(unsigned i)
{
	do {
		unsigned char buf = static_cast<unsigned char>(i & 0x7F);
		if (i > 0x7F)
			buf |= 0x80;
		write_unsigned_char(buf);
		i >>= 7;
	} while (i);
}
