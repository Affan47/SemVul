krb_print(const u_char *dat)
{
	register const struct krb *kp;

	kp = (struct krb *)dat;

	if (dat >= snapend) {
		fputs(tstr, stdout);
		return;
	}

	switch (kp->pvno) {

	case 1:
	case 2:
	case 3:
		printf(" v%d", kp->pvno);
		break;

	case 4:
		printf(" v%d", kp->pvno);
		krb4_print((const u_char *)kp);
		break;

	case 106:
	case 107:
		fputs(" v5", stdout);

		break;
	}
	return;
}
