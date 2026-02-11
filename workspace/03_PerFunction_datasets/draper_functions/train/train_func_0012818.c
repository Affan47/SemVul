print_tm(FILE * f, const struct tcf_t *tm)
{
	int hz = get_user_hz();
	if (tm->install != 0)
		fprintf(f, " installed %u sec", (unsigned)(tm->install/hz));
	if (tm->lastuse != 0)
		fprintf(f, " used %u sec", (unsigned)(tm->lastuse/hz));
	if (tm->expires != 0)
		fprintf(f, " expires %u sec", (unsigned)(tm->expires/hz));
}
