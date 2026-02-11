getrumor(truth, rumor_buf, exclude_cookie)
int truth;
char *rumor_buf;
boolean exclude_cookie;
{
	dlb	*rumors;
	long tidbit, beginning;
	char	*endp, line[BUFSZ], xbuf[BUFSZ];

	rumor_buf[0] = '\0';
	if (true_rumor_size < 0L)
		return rumor_buf;

	rumors = dlb_fopen(RUMORFILE, "r");

	if (rumors) {
	    int count = 0;
	    int adjtruth;

	    do {
		rumor_buf[0] = '\0';
		if (true_rumor_size == 0L) {
		    init_rumors(rumors);
		    if (true_rumor_size < 0L) {
			Sprintf(rumor_buf, "Error reading \"%.80s\".",
				RUMORFILE);
			return rumor_buf;
		    }
		}


		switch (adjtruth = truth + rn2(2)) {
		  case  2:
		  case  1:  beginning = true_rumor_start;
			    tidbit = Rand() % true_rumor_size;
			break;
		  case  0:
		  case -1:  beginning = false_rumor_start;
			    tidbit = Rand() % false_rumor_size;
			break;
		  default:
			    impossible("strange truth value for rumor");
			return strcpy(rumor_buf, "Oops...");
		}
		(void) dlb_fseek(rumors, beginning + tidbit, SEEK_SET);
		(void) dlb_fgets(line, sizeof line, rumors);
		if (!dlb_fgets(line, sizeof line, rumors) ||
		    (adjtruth > 0 && dlb_ftell(rumors) > true_rumor_end)) {

			(void) dlb_fseek(rumors, beginning, SEEK_SET);
			(void) dlb_fgets(line, sizeof line, rumors);
		}
		if ((endp = index(line, '\n')) != 0) *endp = 0;
		Strcat(rumor_buf, xcrypt(line, xbuf));
	    } while(count++ < 50 && exclude_cookie && (strstri(rumor_buf, "fortune") || strstri(rumor_buf, "pity")));
	    (void) dlb_fclose(rumors);
	    if (count >= 50)
		impossible("Can't find non-cookie rumor?");
	    else
		exercise(A_WIS, (adjtruth > 0));
	} else {
		pline("Can't open rumors file!");
		true_rumor_size = -1;
	}
	return rumor_buf;
}
