ProcessArgs( int argc, char **argv, Opt *options )
#else
ProcessArgs( argc, argv, options )
int argc;
char **argv;
Opt *options;
#endif
{
	Opt *p;
	require(argv!=NULL, "ProcessArgs: command line NULL");

	while ( argc-- > 0 )
	{
		p = options;
		while ( p->option != NULL )
		{
			if ( strcmp(p->option, "*") == 0 ||
				 cistrequ(p->option, *argv))
			{
				if ( p->arg )
				{
					(*p->process)( *argv, *(argv+1) );
					argv++;
					argc--;
				}
				else
					(*p->process)( *argv );
				break;
			}
			p++;
		}
		argv++;
	}
}
