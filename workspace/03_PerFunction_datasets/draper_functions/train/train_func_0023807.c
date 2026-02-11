BsaveHandlers(
  void *theEnv,
  struct constructHeader *theDefclass,
  void *buf)
  {
   DEFCLASS *cls = (DEFCLASS *) theDefclass;
   register unsigned i;
   BSAVE_HANDLER dummy_handler;
   HANDLER *hnd;

   for (i = 0 ; i < cls->handlerCount ; i++)
     {
      hnd = &cls->handlers[i];
      dummy_handler.system = hnd->system;
      dummy_handler.type = hnd->type;
      dummy_handler.minParams = hnd->minParams;
      dummy_handler.maxParams = hnd->maxParams;
      dummy_handler.localVarCount = hnd->localVarCount;
      dummy_handler.cls = DefclassIndex(hnd->cls);
      dummy_handler.name = (long) hnd->name->bucket;
      if (hnd->actions != NULL)
        {
         dummy_handler.actions = ExpressionData(theEnv)->ExpressionCount;
         ExpressionData(theEnv)->ExpressionCount += ExpressionSize(hnd->actions);
        }
      else
        dummy_handler.actions = -1L;
      GenWrite((void *) &dummy_handler,(UNLN) sizeof(BSAVE_HANDLER),(FILE *) buf);
     }
  }
