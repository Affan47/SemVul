_g_rand_string (int len)
{
	static char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	static int   letters_only = 52;
	static int   whole_alphabet = 62;
	char        *s;
	GRand       *rand_gen;
	int          i;

	s = g_malloc (sizeof (char) * (len + 1));
	rand_gen = g_rand_new ();
	for (i = 0; i < len; i++)
		s[i] = alphabet[g_rand_int_range (rand_gen, 0, (i == 0) ? letters_only : whole_alphabet)];
	g_rand_free (rand_gen);
	s[len] = 0;

	return s;
}
