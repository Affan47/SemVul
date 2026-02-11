KeyInit(unsigned char in_pinlen, unsigned char *in_pin, unsigned char *in_bdaddr,
					 unsigned char *in_rand, unsigned char *out_kinit)
{
	unsigned char pinprime[16];
	unsigned char pinlenprime;
	int i, j;


	for (i = 0; i < 16;) {
		for (j = 0; (j < in_pinlen) && (i < 16); j++) {
			pinprime[i] = in_pin[j];
			i++;
		}
		for (j = 0; (j < 6) && (i < 16); j++) {
			pinprime[i] = in_bdaddr[j];
			i++;
		}
	}

	pinlenprime = (in_pinlen + 6 < 16) ? in_pinlen + 6 : 16;

	BTCrackStep3(pinprime, in_rand, pinlenprime, out_kinit);
	return 0;
}
