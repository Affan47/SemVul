jalali_create_date_from_days(struct jtm* j)
{
	int p = j->tm_yday;
	if (p > 365 || p < 0)
		return -1;

	p++;
	int i;


	for (i=0; i<11; i++) {
		if (p > jalali_month_len[i])
			p -= jalali_month_len[i];
		else
			break;
	}

	j->tm_mday = p;
	j->tm_mon = i;

	return 0;
}
