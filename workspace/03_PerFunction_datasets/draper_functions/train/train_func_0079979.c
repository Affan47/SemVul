analyze(void)
{
    if (equation_stat == -1)
	G_warning(_("Poorly placed control points"));
    else if (equation_stat == -2)
	G_fatal_error(_("Insufficient memory"));
    else if (equation_stat < 0)
	G_fatal_error(_("Parameter error"));
    else if (equation_stat == 0)
	G_fatal_error(_("No active control points"));
    else if (summary) {
	printf("Number of active points: %d\n", count);
	do_stats("Forward", &fwd);
	do_stats("Reverse", &rev);
    }
}
