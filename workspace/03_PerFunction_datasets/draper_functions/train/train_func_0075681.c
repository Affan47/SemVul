job_set_queue_info_in_task(const char *qualified_hostname, const char *qname, lListElem *petep)
{
   lListElem *jge;

   DENTER(TOP_LAYER, "job_set_queue_info_in_task");

   jge = lAddSubStr(petep, JG_qname, qname,
                    PET_granted_destin_identifier_list, JG_Type);
   lSetHost(jge, JG_qhostname, qualified_hostname);
   lSetUlong(jge, JG_slots, 1);
   DPRINTF(("selected queue %s for task\n", qname));

   DRETURN(lGetList(petep, PET_granted_destin_identifier_list));
}
