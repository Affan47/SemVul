flush_iptables_user(char *arg1, char *arg2) {

   FILE *fp;
   char cmd[BSIZE];
   char *substring;
   char line[BSIZE];
   int i;

   char *delim = " ";
   char **tokens = NULL;

   char *fret;
   UNUSED(fret);

    if ( (i = status_iptables_user(arg1)) == 0)
       return(1);

    substring = (char*) malloc(strlen(arg2));
    strncpy(substring, arg2+13, strlen(arg2));

    if ( strcmp( substring, "no") == 0 ) {
        sprintf( cmd, "%s -L OUTPUT --line-numbers -n %s | grep TCOS_TNC | awk '{if ($(NF-3) == %d || $(NF-3) == \"%s\") print $1}' | tac | tr \"\\n\" \" \"", IPTABLES, DEVNULL, (int)get_uid(arg1), arg1);
    }
    else {
        sprintf( cmd, "%s -L OUTPUT --line-numbers -n %s | grep TCOS_TNC | awk '{if (($(NF-3) == %d || $(NF-3) == \"%s\")  && ($3 == \"tcp\")) print $1}' | tac | tr \"\\n\" \" \"", IPTABLES, DEVNULL, (int)get_uid(arg1), arg1);
    }

    free(substring);

    if ((fp=(FILE*)popen(cmd, "r")) != NULL) {
       fret=fgets( line, sizeof line, fp);
       pclose(fp);
       if( line[strlen(line)-1] == '\n' )
         line[strlen(line)-1] = 0;

       tokens = split(line, delim);
       for(i = 0; tokens[i] != NULL; i++){
          sprintf( cmd, "%s -D OUTPUT %s %s", IPTABLES, tokens[i], DEVNULL);
#ifdef DEBUG
          debug("flush_iptables_user() %s\n",cmd);
#endif
          if ((fp=(FILE*)popen(cmd, "r")) != NULL)
             pclose(fp);
       }
       for(i = 0; tokens[i] != NULL; i++) {
         free(tokens[i]);
       }
       free(tokens);
       return(1);
    }
    return(0);
}
