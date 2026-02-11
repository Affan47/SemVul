cqueue_delete(sge_gdi_ctx_class_t *ctx, lList **answer_list, const char *name)
{
   bool ret = true;

   DENTER(TOP_LAYER, "cqueue_delete");
   if (name != NULL) {
      lListElem *cqueue = cqueue_create(answer_list, name);

      if (cqueue != NULL) {
         ret &= cqueue_add_del_mod_via_gdi(ctx, cqueue, answer_list, SGE_GDI_DEL);
      }

      lFreeElem(&cqueue);
   }
   DRETURN(ret);
}
