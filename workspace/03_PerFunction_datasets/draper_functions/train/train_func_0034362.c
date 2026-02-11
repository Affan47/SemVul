GetListConstraint(char *lval,struct Promise *pp)

{ struct Constraint *cp;
  struct Rlist *retval = NULL;

for (cp = pp->conlist; cp != NULL; cp=cp->next)
   {
   if (strcmp(cp->lval,lval) == 0)
      {
      if (IsDefinedClass(cp->classes))
         {
         if (retval != NULL)
            {
            CfOut(cf_error,""," !! Multiple \"%s\" int constraints break this promise\n",lval);
            PromiseRef(cf_error,pp);
            }
         }
      else
         {
         continue;
         }

      if (cp->type != CF_LIST)
         {
         CfOut(cf_error,""," !! Type mismatch on rhs - expected type for list constraint \"%s\" \n",lval);
         PromiseRef(cf_error,pp);
         FatalError("Aborted");
         }

      retval = (struct Rlist *)cp->rval;
      }
   }

return retval;
}
