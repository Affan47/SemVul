write_setup(void)
{
    output("%%%%BeginSetup\n");

    output("%d %d translate\n", left, bot);

    if (landscape)
	output("90 rotate 0 1 -1 scale\n");
    else
	output("0 %d translate 1 -1 scale\n", height);

    output("%d %d BEGIN\n", width, height);

    output("%%%%EndSetup\n");
    output("%%%%Page: 1 1\n");
}
