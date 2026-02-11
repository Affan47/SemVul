LookupDefclassInScope(
  void *theEnv,
  char *className)
  {
   DEFCLASS *cls;
   SYMBOL_HN *classSymbol;

   if ((classSymbol = FindSymbolHN(theEnv,className)) == NULL)
     return(NULL);
   cls = DefclassData(theEnv)->ClassTable[HashClass(classSymbol)];
   while (cls != NULL)
     {
      if ((cls->header.name == classSymbol) && DefclassInScope(theEnv,cls,NULL))
        return(cls->installed ? cls : NULL);
      cls = cls->nxtHash;
     }
   return(NULL);
  }
