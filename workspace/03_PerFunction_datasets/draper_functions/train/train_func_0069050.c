show_boxwidth()
{
    SHOW_ALL_NL;

    if (boxwidth < 0.0)
	fputs("\tboxwidth is auto\n", stderr);
    else {
	fprintf(stderr, "\tboxwidth is %g %s\n", boxwidth,
		(boxwidth_is_absolute) ? "absolute" : "relative");
    }
}
