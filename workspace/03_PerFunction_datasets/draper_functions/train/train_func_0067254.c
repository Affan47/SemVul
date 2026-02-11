sge_master_list(const object_description *object_base, const sge_object_type type)
{
   lList **ret = NULL;

   DENTER(OBJECT_LAYER, "sge_master_list");

   if (type >= 0 && type < SGE_TYPE_ALL) {

      if (object_base[type].list != NULL) {
         ret = object_base[type].list;
      } else {
         ERROR((SGE_EVENT, MSG_OBJECT_NO_LIST_TO_MOD_TYPE_SI, SGE_FUNC, type));
      }
   } else {
      ERROR((SGE_EVENT, MSG_OBJECT_INVALID_OBJECT_TYPE_SI, SGE_FUNC, type));
   }

   DRETURN(ret);
}
