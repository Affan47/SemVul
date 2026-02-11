make_fileinv(const char *listing, struct remote_params *rp)
{


  FILE *in;
  char line[4096];
  int number;
  struct fnode *result;

  in = fopen(listing, "r");
  if (!in) {
    fprintf(stderr, "Couldn't open listing file %s\n", listing);
    exit(1);
  }

  number = 1;
  result = new(struct fnode);
  result->next = result->prev = result;

  while (fgets(line, sizeof(line), in)) {
    char *p;
    for (p=line; *p; p++) ;
    while (isspace(*--p)) {
      *p = '\0';
    }
    switch (line[0]) {
      case 'H':
        rp->hostname = copy_data(line);
        break;
      case 'U':
        rp->username = copy_data(line);
        break;
      case 'R':
        rp->remote_root = copy_data(line);
        break;
      case 'F':
        add_file(result, line);
        break;
      case 'D':
        add_directory(result, line);
        break;
      case 'Z':
        delete_entry(result, line);
        break;
      default:
        fprintf(stderr, "Line %d in listing file %s corrupted\n", number, listing);
        break;
    }
    number++;
  }

  fclose(in);
  return result;
}
