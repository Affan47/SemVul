ptf_build_usage_list(char *name, lList *old_usage_list)
{
   lList *usage_list;
   lListElem *usage;

   DENTER(TOP_LAYER, "ptf_build_usage_list");

   if (old_usage_list) {
      usage_list = lCopyList(name, old_usage_list);
      for_each(usage, usage_list) {
         lSetDouble(usage, UA_value, 0);
      }
   } else {
      usage_list = lCreateList(name, UA_Type);

      usage = lCreateElem(UA_Type);
      lSetString(usage, UA_name, USAGE_ATTR_IO);
      lSetDouble(usage, UA_value, 0);
      lAppendElem(usage_list, usage);

      usage = lCreateElem(UA_Type);
      lSetString(usage, UA_name, USAGE_ATTR_IOW);
      lSetDouble(usage, UA_value, 0);
      lAppendElem(usage_list, usage);

      usage = lCreateElem(UA_Type);
      lSetString(usage, UA_name, USAGE_ATTR_MEM);
      lSetDouble(usage, UA_value, 0);
      lAppendElem(usage_list, usage);

      usage = lCreateElem(UA_Type);
      lSetString(usage, UA_name, USAGE_ATTR_CPU);
      lSetDouble(usage, UA_value, 0);
      lAppendElem(usage_list, usage);

#if defined(ALPHA) || defined(LINUX) || defined(SOLARIS) || defined(HP1164) || defined(AIX) || defined(FREEBSD) || defined(DARWIN)
      usage = lCreateElem(UA_Type);
      lSetString(usage, UA_name, USAGE_ATTR_VMEM);
      lSetDouble(usage, UA_value, 0);
      DPRINTF(("adding usage attribute %s\n", USAGE_ATTR_VMEM));
      lAppendElem(usage_list, usage);

      usage = lCreateElem(UA_Type);
      lSetString(usage, UA_name, USAGE_ATTR_MAXVMEM);
      lSetDouble(usage, UA_value, 0);
      DPRINTF(("adding usage attribute %s\n", USAGE_ATTR_MAXVMEM));
      lAppendElem(usage_list, usage);
#endif
   }

   DEXIT;
   return usage_list;
}
