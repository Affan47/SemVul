ntx_editor(char *file)
{
  if(isatty(STDIN_FILENO)) {

    char *editor = getenv("EDITOR");
    pid_t child;

    if(editor) {
      if((child = fork()) == 0) execlp(editor, editor, file, (char*)NULL);
      else waitpid(child, NULL, 0);
    } else die("The environment variable EDITOR is unset.\n");
  } else {
    FILE *f = raw_open(file, "w");
    char buffer[BUFFER_LEN];


    while(fgets(buffer, BUFFER_LEN, stdin)) fputs(buffer, f);
    release(f);
  }
}
