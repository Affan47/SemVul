qinstance_set_slots_used(lListElem *this_elem, int new_slots)
{
   lListElem *slots;

   DENTER(QINSTANCE_LAYER, "qinstance_set_slots_used");
   slots = lGetSubStr(this_elem, RUE_name, "slots", QU_resource_utilization);
   if (slots != NULL) {
      lSetDouble(slots, RUE_utilized_now, new_slots);
   } else {

      CRITICAL((SGE_EVENT, MSG_QINSTANCE_MISSLOTS_S,
                lGetString(this_elem, QU_full_name)));
   }

   DRETURN_VOID;
}
