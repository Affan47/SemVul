DeclarationParse(
  void *theEnv,
  char *readSource,
  char *ruleName,
  int *error)
  {
   struct token theToken;
   struct expr *packPtr;
   int notDone = TRUE;
   int salienceParsed = FALSE, autoFocusParsed = FALSE;


   SavePPBuffer(theEnv," ");

   GetToken(theEnv,readSource,&theToken);
   if (theToken.type != LPAREN)
     {
      SyntaxErrorMessage(theEnv,"declare statement");
      *error = TRUE;
      return;
     }


   while (notDone)
     {


      GetToken(theEnv,readSource,&theToken);
      if (theToken.type != SYMBOL)
        {
         SyntaxErrorMessage(theEnv,"declare statement");
         *error = TRUE;
        }


      else if (strcmp(ValueToString(theToken.value),"salience") == 0)
        {
         if (salienceParsed)
           {
            AlreadyParsedErrorMessage(theEnv,"salience declaration",NULL);
            *error = TRUE;
           }
         else
           {
            ParseSalience(theEnv,readSource,ruleName,error);
            salienceParsed = TRUE;
           }
        }


      else if (strcmp(ValueToString(theToken.value),"auto-focus") == 0)
        {
         if (autoFocusParsed)
           {
            AlreadyParsedErrorMessage(theEnv,"auto-focus declaration",NULL);
            *error = TRUE;
           }
         else
           {
            ParseAutoFocus(theEnv,readSource,error);
            autoFocusParsed = TRUE;
           }
         }


       else
        {
         SyntaxErrorMessage(theEnv,"declare statement");
         *error = TRUE;
        }


      if (*error)
        {
         ReturnExpression(theEnv,PatternData(theEnv)->SalienceExpression);
         PatternData(theEnv)->SalienceExpression = NULL;
         return;
        }


      GetToken(theEnv,readSource,&theToken);
      if (theToken.type != RPAREN)
        {
         PPBackup(theEnv);
         SavePPBuffer(theEnv," ");
         SavePPBuffer(theEnv,theToken.printForm);
         ReturnExpression(theEnv,PatternData(theEnv)->SalienceExpression);
         PatternData(theEnv)->SalienceExpression = NULL;
         SyntaxErrorMessage(theEnv,"declare statement");
         *error = TRUE;
         return;
        }


      GetToken(theEnv,readSource,&theToken);
      if (theToken.type == RPAREN) notDone = FALSE;
      else if (theToken.type != LPAREN)
        {
         ReturnExpression(theEnv,PatternData(theEnv)->SalienceExpression);
         PatternData(theEnv)->SalienceExpression = NULL;
         SyntaxErrorMessage(theEnv,"declare statement");
         *error = TRUE;
         return;
        }
      else
        {
         PPBackup(theEnv);
         SavePPBuffer(theEnv," (");
        }
     }


   packPtr = PackExpression(theEnv,PatternData(theEnv)->SalienceExpression);
   ReturnExpression(theEnv,PatternData(theEnv)->SalienceExpression);
   PatternData(theEnv)->SalienceExpression = packPtr;
   return;
  }
