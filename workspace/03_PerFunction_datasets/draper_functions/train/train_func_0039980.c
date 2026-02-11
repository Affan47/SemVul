object_type_commit_master_list(const sge_object_type type, lList **answer_list)
{
   bool ret = true;

   DENTER(OBJECT_LAYER, "object_type_set_master_list");

   if (type >= 0 && type < SGE_TYPE_ALL) {

      if (object_base[type].commitMasterList) {
         ret = object_base[type].commitMasterList(answer_list);
      }
   } else {
         ERROR((SGE_EVENT, MSG_OBJECT_INVALID_OBJECT_TYPE_SI, SGE_FUNC, type));
         ret = false;
   }

   DRETURN(ret);
}
