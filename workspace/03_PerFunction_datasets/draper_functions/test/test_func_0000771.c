generate_rand_pw(int len)
{
	static char pass[PASSSIZE+1];
	int i, j;

	pass[0] = 0;

	if (seed == 1L)
		conv_randomize();

	if (len < 1)
		return pass;

	if (len > PASSSIZE)
		len = PASSSIZE;

        for (i = 0; i < len; i++) {
                j = conv_random(10+26*2, 0);
                if (j < 10) {
                        pass[i] = j + '0';
                        continue;
                }
                j -= 10;
                if (j < 26) {
                        pass[i] = j + 'A';
			continue;
                }
                j -= 26;
                pass[i] = j + 'a';
        }
        pass[len] = 0;

        return pass;
}
