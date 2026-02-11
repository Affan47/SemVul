vbProcessPINInterval (
	int pin_length,
	unsigned long pin_start,
	unsigned long pin_end,
	char *sPin,
	char *sLinkKey,
	unsigned long *PinsPerSec)
{
	long pins_per_thread;
	int  who_solved = 0;
	pthread_t g_hThreadHandle[MAX_THREADS];
	unsigned long total_pins = 0;
	long i;

	pins_per_thread = (pin_end - pin_start + 1)/t_max;
	pin_solved = 0;


	for (i=0; i<t_max; i++)	{
		BTCrackArray[i].pin_start = pin_start + i*pins_per_thread;
		BTCrackArray[i].pin_end = BTCrackArray[i].pin_start + pins_per_thread - 1;
		BTCrackArray[i].pinlen = pin_length;

		pthread_create(&g_hThreadHandle[i], NULL, DoThreadProcessing, &BTCrackArray[i]);
	}

	for (i=0; i<t_max; i++) {
		pthread_join(g_hThreadHandle[i], NULL);

		g_hThreadHandle[i] = 0;
		total_pins = total_pins + BTCrackArray[i].pins_per_sec;

		if (BTCrackArray[i].pin_solved == 1) {
			pin_solved = 1;
			who_solved = i;
		}
	}

	*PinsPerSec += total_pins;
	if (pin_solved) {
		sprintf(sPin, "%s",(char *) BTCrackArray[who_solved].pin);
		sprintf(sLinkKey, "%s", (char *) BTCrackArray[who_solved].link_key);
		return 0;
	}

	return -1;
}
