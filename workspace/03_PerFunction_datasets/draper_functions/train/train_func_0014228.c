printoneline(acarsmsg_t * msg, int chn, time_t t)
{
	char txt[60];
	char *pstr;

	strncpy(txt, msg->txt, 60);
	txt[59] = 0;

	for (pstr = txt; *pstr != 0; pstr++)
		if (*pstr == '\n' || *pstr == '\r')
			*pstr = ' ';

	if (channel[chn].inmode == 3)
		fprintf(fdout, "#%1d (L:%3d E:%1d) ", chn + 1, msg->lvl,
			msg->err);
	else
		fprintf(fdout, "#%1d (E:%1d) ", chn + 1, msg->err);

	if (channel[chn].inmode != 2)
		printtime(t);


	if (msg->fid[0] == '\0' && msg->no[0] == '\0')
		fprintf(fdout, " %7s %1c %2s ", msg->addr, msg->mode,
			msg->label);
	else
		fprintf(fdout, " %7s %6s %1c %2s %4s ", msg->addr, msg->fid,
			msg->mode, msg->label, msg->no);

	fprintf(fdout, "%s", txt);
	fprintf(fdout, "\n");
	fflush(fdout);
}
