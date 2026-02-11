cqueue_list_del_all_orphaned(sge_gdi_ctx_class_t *ctx, lList *this_list, lList **answer_list, const char *cqname, const char *ehname)
{
   bool ret = true;
   lListElem *cqueue;

   DENTER(TOP_LAYER, "cqueue_list_del_all_orphaned");

   if (cqname) {
      cqueue = lGetElemStr(this_list, CQ_name, cqname);
      ret &= cqueue_del_all_orphaned(ctx, cqueue, answer_list, ehname);
   } else {
      for_each(cqueue, this_list) {
         ret &= cqueue_del_all_orphaned(ctx, cqueue, answer_list, ehname);
         if (!ret) {
            break;
         }
      }
   }

   DEXIT;
   return ret;
}
