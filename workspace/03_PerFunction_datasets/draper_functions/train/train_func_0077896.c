qinstance_is_a_pe_referenced(const lListElem *this_elem)
{
   bool ret = false;

   DENTER(TOP_LAYER, "qinstance_is_a_pe_referenced");
   if (lGetNumberOfElem(lGetList(this_elem, QU_pe_list))) {
      ret = true;
   }
   DRETURN(ret);
}
