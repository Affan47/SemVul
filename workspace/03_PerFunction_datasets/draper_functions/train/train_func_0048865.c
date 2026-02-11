GetElementAtPos (unsigned start, unsigned &end)
{
	int Z;
	char text[4];
	memset (text, 0, 4);
	strncpy (text, m_buf.c_str () + start, 3);
	for (unsigned i = MIN (strlen (text), end - start); i > 0; i--) {
		text[i] = 0;
		if ((Z = Element::Z (text))) {
			end = start + i;
			return Z;
		}
	}
	return 0;
}
