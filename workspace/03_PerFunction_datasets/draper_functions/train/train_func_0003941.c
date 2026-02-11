viewj(const struct spq * jp)
{
	int		haspages = 0;
	char		*delim = (char *) 0;
	unsigned	pagenums = 0;
	LONG		*pageoffs = (LONG *) 0;
	FILE		*ifl;
	struct	pages	pfe;

	if  (pagearg  &&  (haspages = rdpgfile(jp, &pfe, &delim, &pagenums, &pageoffs)) < 0)
		nomem();
	if  (jp->spq_netid)
		ifl = net_feed(FEED_NPSP, jp->spq_netid, jp->spq_rslot, jp->spq_job);
	else
		ifl = fopen(mkspid(SPNAM, jp->spq_job), "r");

	if  (!ifl)  {
		disp_arg[0] = jp->spq_job;
		if  (jp->spq_netid)  {
			disp_str = look_host(jp->spq_netid);
			print_error(139);
		}
		else
			print_error(138);
		goto  endview;
	}
	if  (pagearg)  {
		LONG	current_offset = 0L;
		unsigned  current_page = 1;
		int	rg, ch = ' ';
		if  (haspages)  {
			while  ((rg = inrange(current_page)) >= 0)  {
				if  (rg == 0)  {
					while  (current_offset < pageoffs[current_page]  &&  (ch = getc(ifl)) != EOF)
						current_offset++;
				}
				else  while  (current_offset < pageoffs[current_page]  &&  (ch = getc(ifl)) != EOF)  {
					current_offset++;
					putchar(ch);
				}
				if  (ch == EOF)
					break;
				current_page++;
			}
		}
		else  {
			while  ((rg = inrange(current_page)) >= 0)  {
				if  (rg == 0)  {
					while  ((ch = getc(ifl)) != EOF  &&  ch != '\f')
						current_offset++;
					current_offset++;
				}
				else  {
					while  ((ch = getc(ifl)) != EOF)  {
						current_offset++;
						putchar(ch);
						if  (ch == '\f')
							break;
					}
				}
				if  (ch == EOF)
					break;
				current_page++;
			}
		}
	}
	else  {
		int	ch;
		while  ((ch = getc(ifl)) != EOF)
			putchar(ch);
	}
	fclose(ifl);
endview:
	if  (haspages)  {
		free(delim);
		free((char *) pageoffs);
	}
}
