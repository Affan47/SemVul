responsible_queue(lListElem *jep, lListElem *jatep, lListElem *petep)
{
   lListElem *master_q = NULL;

   DENTER(TOP_LAYER, "responsible_queue");

   if (petep == NULL) {
      master_q = lGetObject(lFirst(lGetList(jatep, JAT_granted_destin_identifier_list)), JG_queue);
   } else {
      lListElem *pe_queue = lFirst(lGetList(petep, PET_granted_destin_identifier_list));
      master_q = lGetObject(lGetElemStr(lGetList(jatep, JAT_granted_destin_identifier_list),
                            JG_qname, lGetString(pe_queue, JG_qname)), JG_queue);

   }

   DRETURN(master_q);
}
