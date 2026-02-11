get_line(char s[], char w[], FILE *file, char **assigner, char **value, int wide)
{
  int l,q;
  char *b;
  char *c;

  *assigner = NULL;
  *value = NULL;

  do {

    s[0] = 0;
    my_fgets(s, w, MAXLINE, file, wide);
    s[MAXLINE] = 0;
    b = s;

    l = strlen(s);

#ifdef GETLINE_DEBUG
    printf("get_line: read line len %d : %s\n",l,s);
#endif

    if (l == 0) {
      if (feof(file)) return 0;
      break;
    }

    while (isspace(*b)) b++;
    c = b;
    while (*c && *c != '\n' && *c != '\r') c++;
    *c = 0;


    if (!*b) continue;

    l = strlen(s);

#ifdef GETLINE_DEBUG
    printf("get_line: stripped line len %d : %s\n",l,s);
#endif


    c = b;

    if (*b == '[') {
#ifdef GETLINE_DEBUG
      printf("get_line: key line..\n");
#endif
      while (*c && (*c != ']')) c++;
      if (!*c) {
	printf("get_line: WARNING: un-terminated key line..\n");
      }
      *c = 0;
      *assigner = b+1;
      *value = NULL;
      return(l);
    }

    q = 0;
    while (*c) {

      if (*c == '"') q ^= 1;
      if (*c == '=' && !q) {
	*c = 0;
	*assigner = b;
	*value = c + 1;
#ifdef GETLINE_DEBUG
	printf("get_line: value line\n");
#endif
	return(l);
      }
      c++;
    }

    *assigner = NULL;
    *value = b;
#ifdef GETLINE_DEBUG
    printf("get_line: cont line\n");
#endif
    return(l);

  } while (!feof(file));

  return(l);
}
