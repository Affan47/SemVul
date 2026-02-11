main(int argc, char *argv[]) {


  int number = 0;
  int encrypt = 0;
  int decrypt = 0;
  int ch = 0;

  char *envalue = NULL;
  char *progname;


  int letter = 97;
  for (int i = 0; i < SIZE; i++) {
    enArray[i] = letter;
    letter += 1;
  }

  progname = argv[0];


  struct option LONG_OPTS[] = {
    { "help", no_argument, NULL, 'h'},
    {NULL, 0, NULL, 0}
  };


  while ((ch = getopt_long(argc, argv, "nm:M:", LONG_OPTS, NULL)) != -1) {

       switch (ch) {

       case 'n':
            number = 1;
            break;
       case 'm':
            encrypt = 1;
            envalue = optarg;
            encryption(envalue, encrypt, decrypt);
            break;
       case 'M':
            decrypt = 1;
            envalue = optarg;
            encryption(envalue, encrypt, decrypt);
            break;

       case 'h':
            fprintf(stdout, "dog Version 1.0:\n"
            "--help option:\nUsage: dog [OPTION]... [FILE]...\n"
            "Concatenate FILE(s), or standard input, to standard output.\n\n"

            "-n, begin each output line with a line number corresponding to its position in the concatenated (cumulative) input.\n\n"

            "-m mapfile, use a simple substitution cipher to very weakly encrypt its inputs.\n"
            "The file specified (e.g., mapfile) should contain 26 lines containing pairs of letters where the first letter is a plaintext letter and the second is the ciphertext equivalent."
            "As the characters are read from the input(s), each letter should be transformed according to the corresponding mapping in the mapfile.\n\n"

            "-M mapfile, decipher its input(s) back into plaintext. Thus, the mapfile is read and the opposite procedure is used to decipher the input.\n\n"

            "--help, displays help information for dog, including version information.\n\n"

            "With no FILE, or when FILE is -, read standard input.\n\n"

            "Examples:\n"
            "\tdog -m mapfile inputfile --> Encrypt inputfile using mapfile as a cypher and output encrypted contents to stdout.\n"
            "\tdog f - g --> Output f's contents, then stdin, then g's contents\n\n");

            exit (EXIT_SUCCESS);
            break;

       default:
            fprintf(stderr, "Error: bad option \'%c\'\n", ch);
            fprintf(stderr, "Usage:  %s [-n] [-m] [-M] \n", progname);
            exit (EXIT_FAILURE);
            break;
       }
  }

  FILE *fp;


  if ( optind == argc ) {
    fp = stdin;
    processOutput(fp, number, encrypt, decrypt);
  }


  else {


    if (( 45 == *argv[optind] )) {
      fp = stdin;
      processOutput(fp, number, encrypt, decrypt);
    }

    else {


      for ( int i = optind; i < argc; i++ ) {
        fp = fopen(argv[i], "r");
        if ( NULL != fp ) {
          processOutput(fp, number, encrypt, decrypt);
          fclose(fp);
        }


        else if ((45 == *argv[i])) {
          fp = stdin;
          processOutput(fp, number, encrypt, decrypt);
        }

        else {
          fprintf(stderr, "Error opening file, file is NULL or non-existent");
          exit (EXIT_FAILURE);
        }
      }
    }
  }
  return(0);
}
