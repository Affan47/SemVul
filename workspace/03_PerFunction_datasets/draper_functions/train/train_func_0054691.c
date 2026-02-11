usage_list_set_double_usage(lList *usage_list, const char *name, double value)
{
   lListElem *ep = lGetElemStr(usage_list, UA_name, name);
   if (ep == NULL) {
      ep = lAddElemStr(&usage_list, UA_name, name, UA_Type);
   }

   lSetDouble(ep, UA_value, value);
}
