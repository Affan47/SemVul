onesixty_add_mod(onesixty *sum, onesixty *a, onesixty *b)
{
	uint32_t s;
	int i, carry;

	carry = 0;
	for(i=19; i>=0; i--) {

		s = a->p[i] + b->p[i] + carry;
		sum->p[i] = s & 0xff;
		carry = s >> 8;
	}
}
