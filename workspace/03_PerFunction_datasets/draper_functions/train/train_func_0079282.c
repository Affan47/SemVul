reorder(void)
{
  int i;
  char **files, **options;
  files   = new char*[argc];
  options = new char*[argc];


  for (i=1; i<argc; ++i)
    {
      if ('-' == argv[i][0])
	{
	  if ('-' == argv[i][1])
	    {


	      files[i] = 0;
	      options[i] = 0;
	      for(++i; i<argc; ++i)
		{
		  files[i] = argv[i];
		  options[i] = 0;
		}
	    }
	  else
	    {

	      options[i] = argv[i];
	      files[i] = 0;
	    }
	}
      else
	{
	  files[i] = argv[i];
	  options[i] = 0;
	}
    }


  int n = 1;
  for (i=1; i<argc; ++i)
    {
      if (options[i])
	argv[n++] = options[i];
    }
  for (i=1; i<argc; ++i)
    {
      if (files[i])
	argv[n++] = files[i];
    }
  for (i=n; i<argc; ++i)
    {
      argv[i] = 0;
    }

  argc = n;

  delete[] files;
  delete[] options;

}
