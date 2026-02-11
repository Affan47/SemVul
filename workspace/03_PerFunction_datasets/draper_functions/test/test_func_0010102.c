MarkNeededItems(
  void *theEnv,
  struct expr *testPtr)
  {
   while (testPtr != NULL)
     {
      switch (testPtr->type)
        {
         case SYMBOL:
         case STRING:
         case GBL_VARIABLE:
         case INSTANCE_NAME:
            ((SYMBOL_HN *) testPtr->value)->neededSymbol = TRUE;
            break;

         case FLOAT:
            ((FLOAT_HN *) testPtr->value)->neededFloat = TRUE;
            break;

         case INTEGER:
            ((INTEGER_HN *) testPtr->value)->neededInteger = TRUE;
            break;

         case FCALL:
            ((struct FunctionDefinition *) testPtr->value)->bsaveIndex = TRUE;
            break;

         case RVOID:
           break;

         default:
           if (EvaluationData(theEnv)->PrimitivesArray[testPtr->type] == NULL) break;
           if (EvaluationData(theEnv)->PrimitivesArray[testPtr->type]->bitMap)
             { ((BITMAP_HN *) testPtr->value)->neededBitMap = TRUE; }
           break;

        }

      if (testPtr->argList != NULL)
        { MarkNeededItems(theEnv,testPtr->argList); }

      testPtr = testPtr->nextArg;
     }
  }
