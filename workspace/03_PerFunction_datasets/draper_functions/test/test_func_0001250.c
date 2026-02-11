print_linkmode(FILE *f, struct rtattr *tb)
{
	unsigned int mode = rta_getattr_u8(tb);

	if (mode >= sizeof(link_modes) / sizeof(link_modes[0]))
		fprintf(f, "mode %d ", mode);
	else
		fprintf(f, "mode %s ", link_modes[mode]);
}
