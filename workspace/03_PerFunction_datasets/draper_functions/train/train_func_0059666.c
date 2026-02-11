RemoveConstraint(
  void *theEnv,
  struct constraintRecord *theConstraint)
  {
   struct constraintRecord *tmpPtr, *prevPtr = NULL;

   if (theConstraint == NULL) return;


   if (theConstraint->bucket < 0)
     {
      ReturnConstraintRecord(theEnv,theConstraint);
      return;
     }


   tmpPtr = ConstraintData(theEnv)->ConstraintHashtable[theConstraint->bucket];
   while (tmpPtr != NULL)
     {
      if (tmpPtr == theConstraint)
        {
         theConstraint->count--;
         if (theConstraint->count == 0)
           {
            if (prevPtr == NULL)
              { ConstraintData(theEnv)->ConstraintHashtable[theConstraint->bucket] = theConstraint->next; }
            else
              { prevPtr->next = theConstraint->next; }
            DeinstallConstraintRecord(theEnv,theConstraint);
            ReturnConstraintRecord(theEnv,theConstraint);
           }
         return;
        }

      prevPtr = tmpPtr;
      tmpPtr = tmpPtr->next;
     }

   return;
  }
