RemoveAllExplicitMethods(
  void *theEnv,
  DEFGENERIC *gfunc)
  {
   register unsigned i,j;
   unsigned systemMethodCount = 0;
   DEFMETHOD *narr;

   if (MethodsExecuting(gfunc) == FALSE)
     {
      for (i = 0 ; i < gfunc->mcnt ; i++)
        {
         if (gfunc->methods[i].system)
           systemMethodCount++;
         else
           DeleteMethodInfo(theEnv,gfunc,&gfunc->methods[i]);
        }
      if (systemMethodCount != 0)
        {
         narr = (DEFMETHOD *) gm2(theEnv,(systemMethodCount * sizeof(DEFMETHOD)));
         i = 0;
         j = 0;
         while (i < gfunc->mcnt)
           {
            if (gfunc->methods[i].system)
              GenCopyMemory(DEFMETHOD,1,&narr[j++],&gfunc->methods[i]);
            i++;
           }
         rm(theEnv,(void *) gfunc->methods,(sizeof(DEFMETHOD) * gfunc->mcnt));
         gfunc->mcnt = systemMethodCount;
         gfunc->methods = narr;
        }
      else
        {
         if (gfunc->mcnt != 0)
           rm(theEnv,(void *) gfunc->methods,(sizeof(DEFMETHOD) * gfunc->mcnt));
         gfunc->mcnt = 0;
         gfunc->methods = NULL;
        }
      return(TRUE);
     }
   return(FALSE);
  }
