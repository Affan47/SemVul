CopyLHSParseNode(
  void *theEnv,
  struct lhsParseNode *dest,
  struct lhsParseNode *src,
  int duplicate)
  {
   dest->type = src->type;
   dest->value = src->value;
   dest->negated = src->negated;
   dest->bindingVariable = src->bindingVariable;
   dest->withinMultifieldSlot = src->withinMultifieldSlot;
   dest->multifieldSlot = src->multifieldSlot;
   dest->multiFieldsBefore = src->multiFieldsBefore;
   dest->multiFieldsAfter = src->multiFieldsAfter;
   dest->singleFieldsBefore = src->singleFieldsBefore;
   dest->singleFieldsAfter = src->singleFieldsAfter;
   dest->logical = src->logical;
   dest->userCE = src->userCE;
   dest->referringNode = src->referringNode;
   dest->patternType = src->patternType;
   dest->pattern = src->pattern;
   dest->index = src->index;
   dest->slot = src->slot;
   dest->slotNumber = src->slotNumber;
   dest->beginNandDepth = src->beginNandDepth;
   dest->endNandDepth = src->endNandDepth;


   if (duplicate)
     {
      dest->networkTest = CopyExpression(theEnv,src->networkTest);
      if (src->userData == NULL)
        { dest->userData = NULL; }
      else if (src->patternType->copyUserDataFunction == NULL)
        { dest->userData = src->userData; }
      else
        { dest->userData = (*src->patternType->copyUserDataFunction)(theEnv,src->userData); }
      dest->expression = CopyLHSParseNodes(theEnv,src->expression);
      dest->constraints = CopyConstraintRecord(theEnv,src->constraints);
      if (dest->constraints != NULL) dest->derivedConstraints = TRUE;
      else dest->derivedConstraints = FALSE;
     }
   else
     {
      dest->networkTest = src->networkTest;
      dest->userData = src->userData;
      dest->expression = src->expression;
      dest->derivedConstraints = FALSE;
      dest->constraints = src->constraints;
     }
  }
