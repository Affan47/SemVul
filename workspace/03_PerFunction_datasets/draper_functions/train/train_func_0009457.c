printBits (std::ostream &os, half h)
{
    unsigned short b = h.bits();

    for (int i = 15; i >= 0; i--)
    {
	os << (((b >> i) & 1)? '1': '0');

	if (i == 15 || i == 10)
	    os << ' ';
    }
}
