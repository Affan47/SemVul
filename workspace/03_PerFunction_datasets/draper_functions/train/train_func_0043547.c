EnvGetMethodRestrictions(
  void *theEnv,
  void *vgfunc,
  unsigned mi,
  DATA_OBJECT *result)
  {
   register unsigned i,j;
   register DEFMETHOD *meth;
   register RESTRICTION *rptr;
   unsigned count;
   int roffset,rstrctIndex;
   MULTIFIELD_PTR theList;

   meth = ((DEFGENERIC *) vgfunc)->methods + FindMethodByIndex((DEFGENERIC *) vgfunc,mi);
   count = 3;
   for (i = 0 ; i < (unsigned) meth->restrictionCount ; i++)
     count += meth->restrictions[i].tcnt + 3;
   theList = (MULTIFIELD_PTR) EnvCreateMultifield(theEnv,count);
   SetpType(result,MULTIFIELD);
   SetpValue(result,theList);
   SetpDOBegin(result,1);
   SetpDOEnd(result,count);
   SetMFType(theList,1,INTEGER);
   SetMFValue(theList,1,EnvAddLong(theEnv,(long) meth->minRestrictions));
   SetMFType(theList,2,INTEGER);
   SetMFValue(theList,2,EnvAddLong(theEnv,(long) meth->maxRestrictions));
   SetMFType(theList,3,INTEGER);
   SetMFValue(theList,3,EnvAddLong(theEnv,(long) meth->restrictionCount));
   roffset = 3 + meth->restrictionCount + 1;
   rstrctIndex = 4;
   for (i = 0 ; i < (unsigned) meth->restrictionCount ; i++)
     {
      rptr = meth->restrictions + i;
      SetMFType(theList,rstrctIndex,INTEGER);
      SetMFValue(theList,rstrctIndex++,EnvAddLong(theEnv,(long) roffset));
      SetMFType(theList,roffset,SYMBOL);
      SetMFValue(theList,roffset++,(rptr->query != NULL) ? EnvTrueSymbol(theEnv) : EnvFalseSymbol(theEnv));
      SetMFType(theList,roffset,INTEGER);
      SetMFValue(theList,roffset++,EnvAddLong(theEnv,(long) rptr->tcnt));
      for (j = 0 ; j < rptr->tcnt ; j++)
        {
         SetMFType(theList,roffset,SYMBOL);
#if OBJECT_SYSTEM
         SetMFValue(theList,roffset++,EnvAddSymbol(theEnv,EnvGetDefclassName(theEnv,rptr->types[j])));
#else
         SetMFValue(theList,roffset++,EnvAddSymbol(theEnv,TypeName(theEnv,ValueToInteger(rptr->types[j]))));
#endif
        }
     }
  }
