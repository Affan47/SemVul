operator+(char const * l, lyx::docstring const & r)
{
	lyx::docstring s;
	for (char const * c = l; *c; ++c) {
		LASSERT(static_cast<unsigned char>(*c) < 0x80, );
		s.push_back(*c);
	}
	s += r;
	return s;
}
