HashedExpressionIndex(
  void *theEnv,
  EXPRESSION *theExp)
  {
   EXPRESSION_HN *exphash,*prv;
   unsigned hashval;

   if (theExp == NULL)
     return(-1L);
   exphash = FindHashedExpression(theEnv,theExp,&hashval,&prv);
   return((exphash != NULL) ? exphash->bsaveID : -1L);
  }
