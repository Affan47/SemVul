eolcmd(FILE *input, BSOCK *UA_sock)
{
   if ((argc > 1) && (strchr("!$%&'()*+,-/:;<>?[]^`{|}~", argk[1][0]) != NULL)) {
      eol = argk[1][0];
   } else if (argc == 1) {
      eol = '\0';
   } else {
      sendit(_("Illegal separator character.\n"));
   }
   return 1;
}
