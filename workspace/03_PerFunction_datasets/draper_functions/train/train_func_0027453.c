lAttributesToString_(const lList *attr_list, dstring *attr){
   const lListElem *attr_elem = NULL;

   if(attr == NULL)
      return false;

   if (lGetNumberOfElem(attr_list) == 0){
      return false;
   }
   else {
      for_each(attr_elem, attr_list) {
         const char *name = lGetString(attr_elem, XMLA_Name);
         const char *value = lGetString(attr_elem, XMLA_Value);

         sge_dstring_sprintf_append(attr, " %s=\"%s\"", name, value);
      }
   }
   return true;
}
