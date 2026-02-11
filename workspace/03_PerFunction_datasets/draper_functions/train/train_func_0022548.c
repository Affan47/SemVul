ParseTypeAttribute(
  void *theEnv,
  char *readSource,
  CONSTRAINT_RECORD *constraints)
  {
   int typeParsed = FALSE;
   int variableParsed = FALSE;
   int theType;
   struct token inputToken;


   SavePPBuffer(theEnv," ");
   for (GetToken(theEnv,readSource,&inputToken);
        inputToken.type != RPAREN;
        GetToken(theEnv,readSource,&inputToken))
     {
      SavePPBuffer(theEnv," ");


      if (inputToken.type == SYMBOL)
        {


         if (variableParsed == TRUE)
           {
            SyntaxErrorMessage(theEnv,"type attribute");
            return(FALSE);
           }


         theType = GetConstraintTypeFromTypeName(ValueToString(inputToken.value));
         if (theType < 0)
           {
            SyntaxErrorMessage(theEnv,"type attribute");
            return(FALSE);
           }


         if (SetConstraintType(theType,constraints))
           {
            SyntaxErrorMessage(theEnv,"type attribute");
            return(FALSE);
           }

         constraints->anyAllowed = FALSE;


         typeParsed = TRUE;
        }


      else if (inputToken.type == SF_VARIABLE)
        {


         if (strcmp(inputToken.printForm,"?VARIABLE") != 0)
           {
            SyntaxErrorMessage(theEnv,"type attribute");
            return(FALSE);
           }


         if (typeParsed || variableParsed)
           {
            SyntaxErrorMessage(theEnv,"type attribute");
            return(FALSE);
           }


         variableParsed = TRUE;
        }


       else
        {
         SyntaxErrorMessage(theEnv,"type attribute");
         return(FALSE);
        }
     }


   PPBackup(theEnv);
   PPBackup(theEnv);
   SavePPBuffer(theEnv,")");


   if ((! typeParsed) && (! variableParsed))
     {
      SyntaxErrorMessage(theEnv,"type attribute");
      return(FALSE);
     }


   return(TRUE);
  }
