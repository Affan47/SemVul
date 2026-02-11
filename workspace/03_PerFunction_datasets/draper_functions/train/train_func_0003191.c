main 	(int argc, char *argv[])
{
	int	i;
	int 	filenames;

	outfile = stdout;


	if (argc < 2)
	{
		usage();
		exit(1);
	}
	else
	{
		filenames = FALSE;
		for (i=1; i< argc; i++)
		{
			if (argv[i][0] == '-' && !filenames)
			{
				switch (argv[i][1])
				{
					case 'h':
						help();
						exit(1);
						break;
					case '-':
						closed[i-1] = TRUE;
						filenames = TRUE;
						break;
					default:
						fprintf(stderr,"assemble: unknown option: -%c\n", argv[i][1]);
						exit(1);
						break;
				}
			}
			else
			{
				infiles[i-1] = fopen(argv[i], "r");
				if (infiles[i-1] == NULL)
				{
					fprintf(stderr, "assemble: file not found: %s\n", argv[i]);
					exit(1);
				}
				else
				{
					closed[i-1] = FALSE;
				}
			}
		}
	}
	numfiles = argc-1;
	read_data ();

	for (i=0; i<numfiles; i++)
	{
		if (!closed[i])
			fclose(infiles[i]);
	}
}
