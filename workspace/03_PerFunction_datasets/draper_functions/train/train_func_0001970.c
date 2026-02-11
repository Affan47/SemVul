nomul(nval, txt)
register int nval;
const char *txt;
{
	if(multi < nval) return;
	u.uinvulnerable = FALSE;
	u.usleep = 0;
	multi = nval;
	if (txt && txt[0])
	  (void) strncpy(multi_txt, txt, BUFSZ);
	else
	  (void) memset(multi_txt, 0, BUFSZ);
	flags.travel = iflags.travel1 = flags.mv = flags.run = 0;
}
