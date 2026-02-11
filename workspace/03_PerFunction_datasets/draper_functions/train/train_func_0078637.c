WhileParse(
  void *theEnv,
  struct expr *parse,
  char *infile)
  {
   struct token theToken;
   int read_first_paren;


   SavePPBuffer(theEnv," ");

   parse->argList = ParseAtomOrExpression(theEnv,infile,NULL);
   if (parse->argList == NULL)
     {
      ReturnExpression(theEnv,parse);
      return(NULL);
     }


   GetToken(theEnv,infile,&theToken);
   if ((theToken.type == SYMBOL) && (strcmp(ValueToString(theToken.value),"do") == 0))
     {
      read_first_paren = TRUE;
      PPBackup(theEnv);
      SavePPBuffer(theEnv," ");
      SavePPBuffer(theEnv,theToken.printForm);
      IncrementIndentDepth(theEnv,3);
      PPCRAndIndent(theEnv);
     }
   else if (theToken.type == LPAREN)
     {
      read_first_paren = FALSE;
      PPBackup(theEnv);
      IncrementIndentDepth(theEnv,3);
      PPCRAndIndent(theEnv);
      SavePPBuffer(theEnv,theToken.printForm);
     }
   else
     {
      SyntaxErrorMessage(theEnv,"while function");
      ReturnExpression(theEnv,parse);
      return(NULL);
     }


   if (ExpressionData(theEnv)->svContexts->rtn == TRUE)
     ExpressionData(theEnv)->ReturnContext = TRUE;
   ExpressionData(theEnv)->BreakContext = TRUE;
   parse->argList->nextArg = GroupActions(theEnv,infile,&theToken,read_first_paren,NULL,FALSE);

   if (parse->argList->nextArg == NULL)
     {
      ReturnExpression(theEnv,parse);
      return(NULL);
     }
   PPBackup(theEnv);
   PPBackup(theEnv);
   SavePPBuffer(theEnv,theToken.printForm);


   if (theToken.type != RPAREN)
     {
      SyntaxErrorMessage(theEnv,"while function");
      ReturnExpression(theEnv,parse);
      return(NULL);
     }

   DecrementIndentDepth(theEnv,3);

   return(parse);
  }
