is_owner_ok(
lListElem *jep,
lList *owner_list
) {
   lListElem *op;

   if (!owner_list)
      return True;

   for_each(op, owner_list) {
      if (!fnmatch(lGetString(op, ST_name), lGetString(jep, JB_owner), 0)) {
         return True;
      }
   }
   return False;
}
