print_long (unsigned long value, int base)
{
    unsigned long i;
    char c;

    for (i = (base == 10 ? 1000000000 : 0x10000000); i != 0; i /= base)
	if (value >= i || i == 1) {
	    c = (value / i) % base;
	    print_char (c + (c <= 9 ? '0' : 'a' - 10));
	}

}
