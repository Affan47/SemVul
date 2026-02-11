one(const char *single)
{
  int n = strlen(single) + 1;
  if (n > maxline) reallocate(line,maxline,n);
  strcpy(line,single);


  if (me == 0 && label_active == 0) {
    if (echo_screen && screen) fprintf(screen,"%s\n",line);
    if (echo_log && logfile) fprintf(logfile,"%s\n",line);
  }


  parse();
  if (command == NULL) return NULL;


  if (label_active && strcmp(command,"label") != 0) return NULL;


  if (execute_command()) {
    char *str = new char[maxline+32];
    sprintf(str,"Unknown command: %s",line);
    error->all(FLERR,str);
  }

  return command;
}
