make_tone_burst(unsigned char *data, float freq, float loudness, int len, int *x)
{
	int     i;
	float   val;

	for (i = 0; i < len; i++) {
		val = loudness * sin((freq * 2.0 * M_PI * (*x)++)/8000.0);
		data[i] = AST_LIN2MU((int)val);
	}


	if (*x >= 8000)
		*x = 0;
	return;
}
