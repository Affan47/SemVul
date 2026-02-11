FIOgetargv(char *cmd)
{
     int           inquote = 0;
     int           insquote = 0;
     int           i;
     static char  *argv[256];
     int           argc = 0;
     char          buf[256];
     char         *cp = buf;

     if (cmd == NULL || strlen(cmd) >= 245)
	  return(NULL);

     for (i=0; cmd[i] != '\0'; i++) {

	  switch (cmd[i]) {

	  case ' ': case '\t':

	       if (insquote || inquote) {
		    *cp = cmd[i]; cp++;
		    break;
	       } else {
		    *cp = '\0';
		    argv[argc++] = strdup(buf);
		    cp = buf;


		    while (cmd[i+1] == ' ' || cmd[i+1] == '\t')
			 i++;
	       }
	       break;

	  case '"':
	       if (!insquote)
		    inquote = 1-inquote;
	       break;

	  case '\'':
	       if (!inquote)
		    insquote = 1-insquote;
	       break;

	  case '\\':

	       if (insquote || inquote) {
		    *cp = cmd[i]; cp++;
	       } else {
		    *cp = cmd[i+1]; cp++; i++;
	       }

	       break;

	  default:
	       *cp = cmd[i]; cp++;
	       break;
	  }
     }
     if (buf != cp) {
	  *cp = '\0';
	  argv[argc++] = strdup(buf);
     }
     argv[argc] = NULL;

     return(argv);
}
