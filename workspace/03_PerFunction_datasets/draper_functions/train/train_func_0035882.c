sge_contained_in_access_list_(const char *user, const char *group,
                                         const lList *acl, const lList *acl_list)
{
   lListElem *acl_search, *acl_found;

   DENTER(TOP_LAYER,"sge_contained_in_access_list_");

   for_each (acl_search, acl) {
      if ((acl_found=lGetElemStr(acl_list, US_name,
            lGetString(acl_search, US_name)))) {

         if (sge_contained_in_access_list(user, group, acl_found, NULL)) {
            DRETURN(1);
         }
      } else {
      	DPRINTF(("cannot find userset list entry \"%s\"\n",
		          lGetString(acl_search, US_name)));
      }
   }
   DRETURN(0);
}
