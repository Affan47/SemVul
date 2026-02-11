GetNthRestriction(
  struct FunctionDefinition *theFunction,
  int position)
  {
   int defaultRestriction = (int) 'u';
   size_t theLength;
   int i = 2;


   if (theFunction == NULL) return(defaultRestriction);

   if (theFunction->restrictions == NULL) return(defaultRestriction);


   theLength = strlen(theFunction->restrictions);

   if (theLength < 3) return(defaultRestriction);


   defaultRestriction = (int) theFunction->restrictions[i];

   if (defaultRestriction == '*') defaultRestriction = (int) 'u';


   if (theLength < (size_t) (position + 3)) return(defaultRestriction);


   return((int) theFunction->restrictions[position + 2]);
  }
