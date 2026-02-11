FactIndexFunction(
  void *theEnv)
  {
   DATA_OBJECT item;


   if (EnvArgCountCheck(theEnv,"fact-index",EXACTLY,1) == -1) return(-1L);


   EnvRtnUnknown(theEnv,1,&item);


   if (GetType(item) != FACT_ADDRESS)
     {
      ExpectedTypeError1(theEnv,"fact-index",1,"fact-address");
      return(-1L);
     }


   if (((struct fact *) GetValue(item))->garbage) return(-1L);

   return (EnvFactIndex(theEnv,GetValue(item)));
  }
