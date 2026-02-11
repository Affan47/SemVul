__print_line_id(struct pid_stats *pst, char c)
{
	char format[32];
	struct passwd *pwdent;

	if (DISPLAY_USERNAME(pidflag) && ((pwdent = getpwuid(pst->uid)) != NULL)) {
		printf(" %8s", pwdent->pw_name);
	}
	else {
		printf(" %5d", pst->uid);
	}

	if (DISPLAY_TID(pidflag)) {

		if (pst->tgid) {

			sprintf(format, "         %c %%9u", c);
		}
		else {

			sprintf(format, " %%9u         %c", c);
		}
	}
	else {
		strcpy(format, " %9u");
	}

	printf(format, pst->pid);
}
