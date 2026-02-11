ReturnLHSParseNodes(
  void *theEnv,
  struct lhsParseNode *waste)
  {
   if (waste != NULL)
     {
      ReturnExpression(theEnv,waste->networkTest);
      ReturnLHSParseNodes(theEnv,waste->right);
      ReturnLHSParseNodes(theEnv,waste->bottom);
      ReturnLHSParseNodes(theEnv,waste->expression);
      if (waste->derivedConstraints) RemoveConstraint(theEnv,waste->constraints);
      if ((waste->userData != NULL) &&
          (waste->patternType->returnUserDataFunction != NULL))
        { (*waste->patternType->returnUserDataFunction)(theEnv,waste->userData); }
      rtn_struct(theEnv,lhsParseNode,waste);
     }
  }
