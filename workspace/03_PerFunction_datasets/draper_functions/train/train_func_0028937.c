get_attribute_list_by_names(lListElem *global, lListElem *host,
                                          lListElem *queue, const lList *centry_list,
                                          lList *attrnames)
{
   lListElem *attr, *elem;
   lList *list = NULL;

   for_each(elem, attrnames) {
      attr = get_attribute_by_name(global, host, queue, lGetString(elem, ST_name), centry_list, DISPATCH_TIME_NOW, 0);
      if (attr) {
         if (!list )
            list = lCreateList("attr", CE_Type);
         lAppendElem(list, attr);
      }
   }

   return list;
}
