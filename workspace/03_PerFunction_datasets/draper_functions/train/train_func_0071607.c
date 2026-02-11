static_rand_alt()
{
	static int x=Rnd_seed;
	int old_x;
	old_x = x;
	x >>= 1;
	if ( old_x & 1 ) {
		x ^= RND_MASK;
	}
	return x;
}
