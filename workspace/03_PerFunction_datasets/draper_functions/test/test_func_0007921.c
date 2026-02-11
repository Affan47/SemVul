FunctionReferenceExpression(
  void *theEnv,
  char *name)
  {
#if DEFGENERIC_CONSTRUCT
   void *gfunc;
#endif
#if DEFFUNCTION_CONSTRUCT
   void *dptr;
#endif
   struct FunctionDefinition *fptr;


#if DEFFUNCTION_CONSTRUCT
   if ((dptr = (void *) LookupDeffunctionInScope(theEnv,name)) != NULL)
     { return(GenConstant(theEnv,PCALL,dptr)); }
#endif


#if DEFGENERIC_CONSTRUCT
   if ((gfunc = (void *) LookupDefgenericInScope(theEnv,name)) != NULL)
     { return(GenConstant(theEnv,GCALL,gfunc)); }
#endif


   if ((fptr = FindFunction(theEnv,name)) != NULL)
     { return(GenConstant(theEnv,FCALL,fptr)); }


   return(NULL);
  }
