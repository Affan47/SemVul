ReadUntilClosingParen(
  void *theEnv,
  char *readSource,
  struct token *inputToken)
  {
   int cnt = 1,lparen_read = FALSE;

   do
     {
      if (lparen_read == FALSE)
        SavePPBuffer(theEnv," ");
      GetToken(theEnv,readSource,inputToken);
      if (inputToken->type == STOP)
        {
         SyntaxErrorMessage(theEnv,"message-handler declaration");
         return(FALSE);
        }
      else if (inputToken->type == LPAREN)
        {
         lparen_read = TRUE;
         cnt++;
        }
      else if (inputToken->type == RPAREN)
        {
         cnt--;
         if (lparen_read == FALSE)
           {
            PPBackup(theEnv);
            PPBackup(theEnv);
            SavePPBuffer(theEnv,")");
           }
         lparen_read = FALSE;
        }
      else
        lparen_read = FALSE;
     }
   while (cnt > 0);

   return(TRUE);
  }
