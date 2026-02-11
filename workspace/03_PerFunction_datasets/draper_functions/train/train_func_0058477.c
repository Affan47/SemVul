userset_list_validate_acl_list(lList *acl_list, lList **alpp)
{
   lListElem *usp;

   DENTER(TOP_LAYER, "userset_list_validate_acl_list");

   for_each (usp, acl_list) {
      if (!lGetElemStr(*object_type_get_master_list(SGE_TYPE_USERSET), US_name, lGetString(usp, US_name))) {
         ERROR((SGE_EVENT, MSG_CQUEUE_UNKNOWNUSERSET_S,
                lGetString(usp, US_name) ? lGetString(usp, US_name) : "<NULL>"));
         answer_list_add(alpp, SGE_EVENT, STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);
         DRETURN(STATUS_EUNKNOWN);
      }
   }

   DRETURN(STATUS_OK);
}
