print_num(uint64_t number, unsigned int format)
{
	if (format & FMT_KILOMEGAGIGA) {
		if (number > 99999) {
			number = (number + 500) / 1000;
			if (number > 9999) {
				number = (number + 500) / 1000;
				if (number > 9999) {
					number = (number + 500) / 1000;
					if (number > 9999) {
						number = (number + 500) / 1000;
						printf(FMT("%4lluT ","%lluT "), (unsigned long long)number);
					}
					else printf(FMT("%4lluG ","%lluG "), (unsigned long long)number);
				}
				else printf(FMT("%4lluM ","%lluM "), (unsigned long long)number);
			} else
				printf(FMT("%4lluK ","%lluK "), (unsigned long long)number);
		} else
			printf(FMT("%5llu ","%llu "), (unsigned long long)number);
	} else
		printf(FMT("%8llu ","%llu "), (unsigned long long)number);
}
