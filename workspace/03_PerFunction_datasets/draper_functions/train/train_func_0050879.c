fill_search_quick(struct searchinfo *p,
	unsigned long msgnum, struct stat *stat_buf)
{
	switch (p->type)	{
	case search_before:
		p->value=0;
		{
		time_t t=decode_date(p->as);

			if (t && timestamp_to_day(stat_buf->st_mtime) < t)
				p->value=1;
		}
		break;
	case search_since:
		p->value=0;
		{
		time_t t=decode_date(p->as);

			if (t && timestamp_to_day(stat_buf->st_mtime) >= t)
				p->value=1;
		}
		break;
	case search_on:
		p->value=0;
		{
		time_t t=decode_date(p->as);

			if (t && timestamp_to_day(stat_buf->st_mtime) == t)
				p->value=1;
		}
		break;
	case search_smaller:
		p->value=0;
		{
		unsigned long n;

			if (sscanf(p->as, "%lu", &n) > 0 &&
				stat_buf->st_size < n)
				p->value=1;
		}
		break;
	case search_larger:
		p->value=0;
		{
		unsigned long n;

			if (sscanf(p->as, "%lu", &n) > 0 &&
				stat_buf->st_size > n)
				p->value=1;
		}
		break;
	case search_orderedsubj:
	case search_references1:
	case search_references2:
	case search_references3:
	case search_references4:
	case search_arrival:
	case search_cc:
	case search_date:
	case search_from:
	case search_reverse:
	case search_size:
	case search_to:


		if (p->as)
		{
			free(p->as);
			p->as=0;
		}

		if (p->bs)
		{
			free(p->bs);
			p->bs=0;
		}

		switch (p->type)	{
		case search_arrival:
			p->as=timestamp_for_sorting(stat_buf->st_mtime);
			p->value=1;
			break;
		case search_size:
			{
			char	buf[NUMBUFSIZE], buf2[NUMBUFSIZE];
			char *q;

				libmail_str_size_t(stat_buf->st_size, buf);
				sprintf(buf2, "%*s", (int)(sizeof(buf2)-1), buf);
				for (q=buf2; *q == ' '; *q++='0')
					;
				p->as=my_strdup(buf2);
				p->value=1;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
