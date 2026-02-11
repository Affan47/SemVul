pop()
{
    if ( gstackp == 0 )
    {
       	fprintf(stderr, "%s: Stack underflow\n", PROGNAME);
	exit(4);
    }
    --gstackp;

    free(gstack[gstackp].s_name);
    free(gstack[gstackp].s_file);
}
