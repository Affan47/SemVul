add_p(PLCI *plci, byte code, byte *p)
{
	word p_length;

	p_length = 0;
	if (p) p_length = p[0];
	add_ie(plci, code, p, p_length);
}
