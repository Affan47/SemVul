get_char (cfile)
	struct parse *cfile;
{

	int c;

	if (cfile->bufix == cfile->buflen) {
#if !defined(LDAP_CONFIGURATION)
		c = EOF;
#else
		if (cfile->read_function != NULL)
			c = cfile->read_function(cfile);
		else
			c = EOF;
#endif
	} else {
		c = cfile->inbuf [cfile->bufix];
		cfile->bufix++;
	}

	if (!cfile->ugflag) {
		if (c == EOL) {
			if (cfile->cur_line == cfile->line1) {
				cfile->cur_line = cfile->line2;
				cfile->prev_line = cfile->line1;
			} else {
				cfile->cur_line = cfile->line1;
				cfile->prev_line = cfile->line2;
			}
			cfile->line++;
			cfile->lpos = 1;
			cfile->cur_line [0] = 0;
		} else if (c != EOF) {
			if (cfile->lpos <= 80) {
				cfile->cur_line [cfile->lpos - 1] = c;
				cfile->cur_line [cfile->lpos] = 0;
			}
			cfile->lpos++;
		}
	} else
		cfile->ugflag = 0;
	return c;
}
