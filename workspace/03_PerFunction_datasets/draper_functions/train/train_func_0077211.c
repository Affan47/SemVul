find_non_zero (gpointer mem, gsize len)
{
	guchar *b, *e;
	gsize sz = 0;
	for (b = (guchar*)mem, e = ((guchar*)mem) + len; b != e; ++b, ++sz) {
		if (*b != 0x00)
			return sz;
	}

	return G_MAXSIZE;
}
