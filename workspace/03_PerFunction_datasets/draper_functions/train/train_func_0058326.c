LHSParseNodesToExpression(
  void *theEnv,
  struct lhsParseNode *nodeList)
  {
   struct expr *newList;

   if (nodeList == NULL)
     { return(NULL); }

   newList = get_struct(theEnv,expr);
   newList->type = nodeList->type;
   newList->value = nodeList->value;
   newList->nextArg = LHSParseNodesToExpression(theEnv,nodeList->right);
   newList->argList = LHSParseNodesToExpression(theEnv,nodeList->bottom);

   return(newList);
  }
