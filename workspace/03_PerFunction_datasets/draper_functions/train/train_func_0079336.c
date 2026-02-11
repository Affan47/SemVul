set_department(lList **alpp, lListElem *job, lList *userset_list)
{
   lListElem *dep;
   const char *owner, *group;

   DENTER(TOP_LAYER, "set_department");


   owner = lGetString(job, JB_owner);
   for_each (dep, userset_list) {

      if (!(lGetUlong(dep, US_type) & US_DEPT))
         continue;

      if (sge_contained_in_access_list(owner, NULL, dep, NULL)) {
         lSetString(job, JB_department, lGetString(dep, US_name));
         DPRINTF(("user %s got department "SFQ"\n",
            owner, lGetString(dep, US_name)));

         DRETURN(1);
      }
   }


   group = lGetString(job, JB_group);
   for_each (dep, userset_list) {

      if (!(lGetUlong(dep, US_type) & US_DEPT))
         continue;

      if (sge_contained_in_access_list(NULL, group, dep, NULL)) {
         lSetString(job, JB_department, lGetString(dep, US_name));
         DPRINTF(("user %s got department \"%s\"\n", owner, lGetString(dep, US_name)));

         DRETURN(1);
      }
   }


   if (lGetElemStr(userset_list, US_name, DEFAULT_DEPARTMENT)) {
      lSetString(job, JB_department, DEFAULT_DEPARTMENT);
      DPRINTF(("user %s got department "SFQ"\n", owner, DEFAULT_DEPARTMENT));
      DRETURN(1);
   }

   ERROR((SGE_EVENT, MSG_SGETEXT_NO_DEPARTMENT4USER_SS, owner, group));
   answer_list_add(alpp, SGE_EVENT, STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);

   DRETURN(0);
}
