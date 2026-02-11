AllVariablesInPattern(
  struct lhsParseNode *orField,
  int pattern)
  {
   struct lhsParseNode *andField;


   for (;
        orField != NULL;
        orField = orField->bottom)
     {


      for (andField = orField;
           andField != NULL;
           andField = andField->right)
        {


         if ((andField->type == SF_VARIABLE) || (andField->type == MF_VARIABLE))
           { if (andField->referringNode->pattern != pattern) return(FALSE); }


         else if ((andField->type == PREDICATE_CONSTRAINT) ||
                  (andField->type == RETURN_VALUE_CONSTRAINT))
           {
            if (AllVariablesInExpression(andField->expression,pattern) == FALSE)
              { return(FALSE); }
           }
        }
     }


   return(TRUE);
  }
