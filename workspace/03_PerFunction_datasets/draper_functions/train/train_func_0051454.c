AssignClassID(
  void *theEnv,
  DEFCLASS *cls)
  {
   register unsigned i;

   if ((DefclassData(theEnv)->MaxClassID % CLASS_ID_MAP_CHUNK) == 0)
     {
      DefclassData(theEnv)->ClassIDMap = (DEFCLASS **) genrealloc(theEnv,(void *) DefclassData(theEnv)->ClassIDMap,
                       (unsigned) (DefclassData(theEnv)->MaxClassID * sizeof(DEFCLASS *)),
                       (unsigned) ((DefclassData(theEnv)->MaxClassID + CLASS_ID_MAP_CHUNK) * sizeof(DEFCLASS *)));
      DefclassData(theEnv)->AvailClassID += (unsigned short) CLASS_ID_MAP_CHUNK;

      for (i = DefclassData(theEnv)->MaxClassID ; i < (unsigned) (DefclassData(theEnv)->MaxClassID + CLASS_ID_MAP_CHUNK) ; i++)
        DefclassData(theEnv)->ClassIDMap[i] = NULL;
     }
   DefclassData(theEnv)->ClassIDMap[DefclassData(theEnv)->MaxClassID] = cls;
   cls->id = DefclassData(theEnv)->MaxClassID++;
  }
