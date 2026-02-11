username_find_init(const char *str, size_t len)
{
	int min, med, max, cmp;

	find.str = str;
	find.len = len;

	if (len == 0) {
		find.index = 0;
		return;
	}

	for (min = 0, max = utable.cnt - 1; min <= max; ) {
		med = (min + max) / 2;
		cmp = strncmp(str,SDSTR(utable.by_name[med]->login),len);
		if (cmp == 0) {


			if (min == max) {
				find.index = med;
				return;
			}
			max = med;
		}
		else if (cmp < 0)
			max = med - 1;
		else
			min = med + 1;
	}

	find.index = utable.cnt;
}
