GetSaveFactsDeftemplateNames(
  void *theEnv,
  struct expr *theList,
  int saveCode,
  int *count,
  int *error)
  {
   struct expr *tempList;
   DATA_OBJECT_PTR theDOArray;
   int i, tempCount;
   struct deftemplate *theDeftemplate = NULL;


   *error = FALSE;


   if (theList == NULL)
     {
      *count = 0;
      return(NULL);
     }


   for (tempList = theList, *count = 0;
        tempList != NULL;
        tempList = tempList->nextArg, (*count)++)
     {  }


   theDOArray = (DATA_OBJECT_PTR) gm3(theEnv,(long) sizeof(DATA_OBJECT) * *count);


   for (tempList = theList, i = 0;
        i < *count;
        tempList = tempList->nextArg, i++)
     {


      EvaluateExpression(theEnv,tempList,&theDOArray[i]);

      if (EvaluationData(theEnv)->EvaluationError)
        {
         *error = TRUE;
         rm3(theEnv,theDOArray,(long) sizeof(DATA_OBJECT) * *count);
         return(NULL);
        }


      if (theDOArray[i].type != SYMBOL)
        {
         *error = TRUE;
         ExpectedTypeError1(theEnv,"save-facts",3+i,"symbol");
         rm3(theEnv,theDOArray,(long) sizeof(DATA_OBJECT) * *count);
         return(NULL);
        }


      if (saveCode == LOCAL_SAVE)
        {
         theDeftemplate = (struct deftemplate *)
                         EnvFindDeftemplate(theEnv,ValueToString(theDOArray[i].value));
         if (theDeftemplate == NULL)
           {
            *error = TRUE;
            ExpectedTypeError1(theEnv,"save-facts",3+i,"local deftemplate name");
            rm3(theEnv,theDOArray,(long) sizeof(DATA_OBJECT) * *count);
            return(NULL);
           }
        }
      else if (saveCode == VISIBLE_SAVE)
        {
         theDeftemplate = (struct deftemplate *)
           FindImportedConstruct(theEnv,"deftemplate",NULL,
                                 ValueToString(theDOArray[i].value),
                                 &tempCount,TRUE,NULL);
         if (theDeftemplate == NULL)
           {
            *error = TRUE;
            ExpectedTypeError1(theEnv,"save-facts",3+i,"visible deftemplate name");
            rm3(theEnv,theDOArray,(long) sizeof(DATA_OBJECT) * *count);
            return(NULL);
           }
        }


      theDOArray[i].type = DEFTEMPLATE_PTR;
      theDOArray[i].value = (void *) theDeftemplate;
     }


   return(theDOArray);
  }
