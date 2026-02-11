part(IRCBot *bot, char *channel, char *format, ...)
{
	int i, l, r;
	int cmp;
	int chanIndex = MAX_CHANS+1;
	va_list ap;
	char partString[BUFFER_LEN] = {0};


	l = 0;
	r = bot->num_chans-1;
	i = (l + r)/2;
	while (chanIndex == MAX_CHANS+1) {
		if ((cmp = strcmp(bot->chans[i], channel)) < 0) {

			l = i+1;
			i = (l + r)/2;
		}
		if (cmp == 0) {

			chanIndex = i;
		}
		if (cmp > 0) {

			r = i-1;
			i = (l + r)/2;
		}
	}


	if (chanIndex == MAX_CHANS+1) {
		return -1;
	}


	free(bot->chans[chanIndex]);


	for (i = chanIndex; i < bot->num_chans-1; i++) {
		bot->chans[i] = bot->chans[i+1];
	}


	bot->num_chans--;
	bot->chans[bot->num_chans] = NULL;

	va_start(ap, format);
	vsnprintf(partString, BUFFER_LEN, format, ap);
	va_end(ap);

	raw(bot, "PART %s :%s", channel, partString);

	return 0;
}
