MinFunction(
  void *theEnv,
  DATA_OBJECT_PTR returnValue)
  {
   DATA_OBJECT argValue;
   int numberOfArguments, i;


   if ((numberOfArguments = EnvArgCountCheck(theEnv,"min",AT_LEAST,1)) == -1)
     {
      returnValue->type = INTEGER;
      returnValue->value = (void *) EnvAddLong(theEnv,0L);
      return;
     }


   if (EnvArgTypeCheck(theEnv,"min",1,INTEGER_OR_FLOAT,returnValue) == FALSE)
     {
      returnValue->type = INTEGER;
      returnValue->value = (void *) EnvAddLong(theEnv,0L);
      return;
     }


   for (i = 2 ; i <= numberOfArguments ; i++)
     {
      if (EnvArgTypeCheck(theEnv,"min",i,INTEGER_OR_FLOAT,&argValue) == FALSE) return;

      if (returnValue->type == INTEGER)
        {
         if (argValue.type == INTEGER)
           {
            if (ValueToLong(returnValue->value) > ValueToLong(argValue.value))
              {
               returnValue->type = argValue.type;
               returnValue->value = argValue.value;
              }
           }
         else
           {
            if ((double) ValueToLong(returnValue->value) >
                         ValueToDouble(argValue.value))
              {
               returnValue->type = argValue.type;
               returnValue->value = argValue.value;
              }
           }
        }
      else
        {
         if (argValue.type == INTEGER)
           {
            if (ValueToDouble(returnValue->value) >
                (double) ValueToLong(argValue.value))
              {
               returnValue->type = argValue.type;
               returnValue->value = argValue.value;
              }
           }
         else
           {
            if (ValueToDouble(returnValue->value) > ValueToDouble(argValue.value))
              {
               returnValue->type = argValue.type;
               returnValue->value = argValue.value;
              }
           }
        }
     }

   return;
  }
