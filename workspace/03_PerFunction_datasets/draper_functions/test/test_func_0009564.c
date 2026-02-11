pe_cq_rejected(const char *pe_name, const lListElem *cq)
{
   const lListElem *alist;
   bool rejected;

   DENTER(TOP_LAYER, "pe_cq_rejected");

   if (!pe_name) {
      DRETURN(false);
   }

   rejected = true;
   for_each (alist, lGetList(cq, CQ_pe_list)) {
      if (lGetSubStr(alist, ST_name, pe_name, ASTRLIST_value)) {
         rejected = false;
         break;
      }
   }

   DRETURN(rejected);
}
