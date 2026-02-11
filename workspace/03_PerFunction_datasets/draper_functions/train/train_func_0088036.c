show_mail_stats(char *user)
{
    struct stat buf;
    char mailfile[200];
    BOOL can_show = FALSE, can_show_date = FALSE;

    if (local_finger) {
	if (prog_config.local_config_bits1 & SHOW_LRMAIL)
	    can_show = TRUE;
    } else {
	if (prog_config.config_bits1 & SHOW_LRMAIL)
	    can_show = TRUE;
    }

    if (local_finger) {
	if (prog_config.local_config_bits1 & SHOW_MRDATE)
	    can_show_date = TRUE;
    } else {
	if (prog_config.config_bits1 & SHOW_MRDATE)
	    can_show_date = TRUE;
    }

    if (can_show) {
	char formatted[80];
	int fm;
	char *cp, *xp, *yp;
	struct passwd *pwent = NULL;


	memset (mailfile, 0, sizeof(mailfile));
	for (cp=prog_config.mailbox_file,xp=mailfile;*cp&&strlen(mailfile)<sizeof(mailfile)-1;cp++) {
	    if (*cp == '$') {
		cp++;
		if (*cp == '$') {
		    *(xp++) = *cp;
		} else if (!strncasecmp(cp,"USER", 4)) {
		    for (yp=user;*yp&&strlen(mailfile)<sizeof(mailfile)-1;yp++)
			*(xp++) = *yp;
		    cp+=3;
		} else if (!strncasecmp(cp,"HOME", 4)) {
		    if (pwent == NULL) {
			pwent = getpwnam (user);
		    }
		    if (pwent)
			for (yp=pwent->pw_dir;*yp&&strlen(mailfile)<sizeof(mailfile)-1;yp++)
			    *(xp++) = *yp;
		    cp+=3;
		}
	    } else
		*(xp++) = *cp;
	}

	USER_PRIVS(nuid, ngid);
	fm = stat(mailfile, &buf);
	NOBODY_PRIVS;

	if (fm != -1) {
	    if (can_show_date)
		strftime(formatted, 80, prog_config.ltime_format,
		    localtime(&buf.st_atime));
	    else
		strftime(formatted, 80, prog_config.stime_format,
		    localtime(&buf.st_atime));

	    if ((int) buf.st_size == 0)
		printf("This user has no mail.\n");
	    else {
		printf("This user last read mail %s\n", (char *) formatted);
		if (buf.st_mtime > buf.st_atime) {
		    char formatted2[80];

		    strftime(formatted2, 80, prog_config.ltime_format,
			localtime(&buf.st_mtime));
		    printf("This user has unread mail since %s\n",
			(char *) formatted2);
		}
	    }
	} else
	    printf("This user has no mail or mail spool.\n");
    }

}
