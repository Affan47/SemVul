main(int argc, char *argv[]) {
  off_t sz = 0;
  char *key = NULL, *key2 = NULL;
  char *infile = NULL, *outfile = NULL;
  struct stat statbuf;
  BCoptions options;
  FILE *infd, *outfd;

  argv += parseArgs(&argc, argv, &options);

  for (; argc > 0; argc--, argv++) {

    if (assignFiles(argv[0], &infile, &outfile, &statbuf, &options, key))
      continue;

    if (!key) {
      key = getkey(options.type);
	  if (!key) {
        if (infile != NULL)
          free(infile);
        if (outfile != NULL)
          free(outfile);
        exit(1);
	  }
      mutateKey(&key, &key2);
    }

    infd = fopen(infile, "rb");
    if (infd == NULL) {
      perror("open(infile)");
      continue;
    }

    if (options.standardout) {
      outfd = stdout;
#ifdef WIN32
      if (_setmode(_fileno(outfd), _O_BINARY) == -1) {
        perror("setmode(outfd)");
        exit(EIO);
      }
#endif
    } else {
      outfd = fopen(outfile, "wb");
    }
    if (outfd == NULL) {
      perror("open(outfile)");
      continue;
    }

    if (options.type == ENCRYPT) {
      options.origsize = statbuf.st_size;

      sz = BFEncrypt(infd, outfd, key, &options);
    } else {
      if ((sz = BFDecrypt(infd, outfd, key, key2, &options)) == 0) {
        fprintf(stderr, "Invalid encryption key for file: %s\n", infile);
        exit(1);
      }
    }

    fclose(infd);
    if (!options.compression)
      fclose(outfd);

    if (options.remove == 1)
      deletefile(infile, options, key, statbuf);
  }

  memset(key, 0, strlen(key));
  memset(key2, 0, strlen(key));
  if (key != NULL)
    free(key);
  if (key2 != NULL)
    free(key2);
  if (infile != NULL)
    free(infile);
  if (outfile != NULL)
    free(outfile);

  if(!sz)
    fprintf(stderr, "No valid files found\n");

  return(0);
}
