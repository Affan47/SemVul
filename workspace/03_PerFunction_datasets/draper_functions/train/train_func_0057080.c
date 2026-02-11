jsv_list_remove(const char *name, const char *context)
{
   bool ret = true;

   DENTER(TOP_LAYER, "jsv_list_remove");
   if (name != NULL && context != NULL) {
      const void *iterator = NULL;
      lListElem *jsv_next;
      lListElem *jsv;

      sge_mutex_lock("jsv_list", SGE_FUNC, __LINE__, &jsv_mutex);
      jsv_next = lGetElemStrFirst(jsv_list, JSV_context, context, &iterator);
      while ((jsv = jsv_next) != NULL) {
         jsv_next = lGetElemStrNext(jsv_list, JSV_context, context, &iterator);

         if ((strcmp(lGetString(jsv, JSV_name), name) == 0) &&
             (strcmp(lGetString(jsv, JSV_context), context) == 0)) {
            lRemoveElem(jsv_list, &jsv);
         }
      }
      sge_mutex_unlock("jsv_list", SGE_FUNC, __LINE__, &jsv_mutex);
   }
   DRETURN(ret);
}
