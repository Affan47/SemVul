GenPNConstant(
  void *theEnv,
  struct lhsParseNode *theField)
  {
   struct expr *top;


   if (theField->patternType->genPNConstantFunction != NULL)
     { return (*theField->patternType->genPNConstantFunction)(theEnv,theField); }


   if (theField->negated)
     { top = GenConstant(theEnv,FCALL,ExpressionData(theEnv)->PTR_NEQ); }
   else
     { top = GenConstant(theEnv,FCALL,ExpressionData(theEnv)->PTR_EQ); }

   top->argList = (*theField->patternType->genGetPNValueFunction)(theEnv,theField);
   top->argList->nextArg = GenConstant(theEnv,theField->type,theField->value);

   return(top);
  }
