ShowLoop(BVertex *first)
{
    int i, n;
    BVertex *p0;
    char buf[32];
    FILE *foo;

    sprintf(buf, "bad%d.dx", nShow++);

    foo = fopen(buf, "w");
    if ( foo )
    {
	n = 0;
	p0 = first;
	do
	{
	    n++;
	} while ((p0 = p0->next) != first);

	fprintf(foo,
    "object \"faces\" class array type int rank 0 items 1 data follows\n0\nattribute \"ref\" string \"loops\"\n");

	fprintf(foo,
    "object \"loops\" class array type int rank 0 items 1 data follows\n0\nattribute \"ref\" string \"edges\"\n");

	fprintf(foo,
    "object \"edges\" class array type int rank 0 items %d data follows\n", n);
	for (i = 0; i < n; i++)
	    fprintf(foo, "%d\n", i);
	fprintf(foo, "attribute \"ref\" string \"positions\"\n");

	fprintf(foo,
    "object \"positions\" class array type float rank 1 shape 3 items %d data follows\n", n);
	for (i = 0, p0 = first; i < n; i++, p0 = p0->next)
	    fprintf(foo, "%f %f 0\n", p0->pos.u, p0->pos.v);

	fprintf(foo,
    "object \"data\" class array type int rank 0 items %d data follows\n", n);
	for (i = 0, p0 = first; i < n; i++, p0 = p0->next)
	    fprintf(foo, "%d\n", p0->id);
	fprintf(foo, "attribute \"dep\" string \"positions\"\n");

	fprintf(foo, "object \"fle\" class field\n");
	fprintf(foo, "    component \"faces\" \"faces\"\n");
	fprintf(foo, "    component \"loops\" \"loops\"\n");
	fprintf(foo, "    component \"edges\" \"edges\"\n");
	fprintf(foo, "    component \"positions\" \"positions\"\n");
	fprintf(foo, "    component \"data\" \"data\"\n");
	fprintf(foo, "end\n");

	fclose(foo);
    }

}
