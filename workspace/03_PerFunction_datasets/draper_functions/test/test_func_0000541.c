mouseinit(void)
{
	char	*term;


	term = mygetenv("TERM", "");
	if (strcmp(term, "emacsterm") == 0 ||
	    strcmp(term, "viterm") == 0) {
		emacsviterm = YES;
		mouse = YES;
	}


	else if (strcmp(mygetenv("MOUSE", ""), "myx") == 0) {
		mouse = YES;
	}
#if UNIXPC
	else if (strcmp(term,"s4") == 0 ||
	         strcmp(term,"s120") == 0 ||
	         strcmp(term,"s90") == 0) {
		int retval;
		struct uwdata uwd;
		struct umdata umd;


		retval = ioctl(1,WIOCGETD,&uwd);
		if(retval || uwd.uw_hs <= 0 || uwd.uw_vs <= 0) {


			if(!strcmp(term,"s4")) {
				uw_hs = 9;
				uw_vs = 12;
			}
			else {
				uw_hs = 6;
				uw_vs = 10;
			}
		}
		else {

			uw_hs = uwd.uw_hs;
			uw_vs = uwd.uw_vs;
		}


		if((retval = ioctl(1,WIOCGETMOUSE,&umd)) != -1) {
			umd.um_flags= MSDOWN+MSUP;
			ioctl(1,WIOCSETMOUSE,&umd);
		}
		unixpcmouse = YES;
	}
#endif
	if (mouse == YES) {
		loadmenu(mainmenu);
	}
}
