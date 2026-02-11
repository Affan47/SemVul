ClearBloadedConstraints(
  void *theEnv)
  {
   if (ConstraintData(theEnv)->NumberOfConstraints != 0)
     {
      genlongfree(theEnv,(void *) ConstraintData(theEnv)->ConstraintArray,
                  (unsigned long) (sizeof(CONSTRAINT_RECORD) *
                                  ConstraintData(theEnv)->NumberOfConstraints));
      ConstraintData(theEnv)->NumberOfConstraints = 0;
     }
  }
