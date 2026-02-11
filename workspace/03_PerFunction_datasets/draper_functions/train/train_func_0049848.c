centry_list_modify(sge_gdi_ctx_class_t *ctx, lList **answer_list)
{
   bool ret = true;

   DENTER(TOP_LAYER, "centry_list_modify");
   if (ret) {
      lList *centry_list = centry_list_get_via_gdi(ctx, answer_list);
      lList *old_centry_list = lCopyList("", centry_list);

      ret &= centry_list_provide_modify_context(ctx, &centry_list, answer_list);
      if (ret) {
         ret &= centry_list_add_del_mod_via_gdi(ctx, &centry_list, answer_list, &old_centry_list);
      }

      lFreeList(&centry_list);
      lFreeList(&old_centry_list);
   }
   DRETURN(ret);
}
