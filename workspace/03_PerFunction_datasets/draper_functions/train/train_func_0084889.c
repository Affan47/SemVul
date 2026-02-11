set_input_file(char *s)
{
  Iostack n;

  if (init == 0) {
    stack = (Iostack) make_list(sizeof(struct iostack));
    if (s == CNULL) {
      IOSTREAM = stdin;
      strcpy(FILENAME, "<stdin>");
    } else {
      IOSTREAM = fopen(s, "r");
      if (IOSTREAM == NULL) {
        fprintf(stderr, "Error: cannot open file \"%s\"\n", s);
        exit(1);
      }
      strcpy(FILENAME, s);
    }
    init = 1;
  } else {
    n = (Iostack) get_node((List)stack);
    n->stream = NULL;
    n->filename = (char *) malloc (sizeof(char)*(strlen(s)+2));
    strcpy(n->filename, s);
    n->oldchar = oldchar;
    n->oldcharvalid = oldcharvalid;
    n->pipe = pipe;
    n->line = line;
    insert((List)n, (List)stack->flink);
  }
}
