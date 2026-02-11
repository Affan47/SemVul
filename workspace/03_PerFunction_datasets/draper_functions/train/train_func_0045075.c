rand32()
{
	if (RAND_MAX == 0x7fff) {
		int random32;

		random32 = (rand() << 16) | rand();

		random32 |= ((rand() & 1) << 15);

		return random32;
	}
	else {

		Assert(RAND_MAX == 0x7fffffff);
		return rand();
	}
}
