AddConstraint(
  void *theEnv,
  struct constraintRecord *theConstraint)
  {
   struct constraintRecord *tmpPtr;
   int hashValue;

   if (theConstraint == NULL) return(NULL);

   hashValue = HashConstraint(theConstraint);

   for (tmpPtr = ConstraintData(theEnv)->ConstraintHashtable[hashValue];
        tmpPtr != NULL;
        tmpPtr = tmpPtr->next)
     {
      if (ConstraintCompare(theConstraint,tmpPtr))
        {
         tmpPtr->count++;
         ReturnConstraintRecord(theEnv,theConstraint);
         return(tmpPtr);
        }
     }

   InstallConstraintRecord(theEnv,theConstraint);
   theConstraint->count = 1;
   theConstraint->bucket = hashValue;
   theConstraint->next = ConstraintData(theEnv)->ConstraintHashtable[hashValue];
   ConstraintData(theEnv)->ConstraintHashtable[hashValue] = theConstraint;
   return(theConstraint);
  }
