sge_gdi_ctx_class_destroy(sge_gdi_ctx_class_t **pst)
{
   DENTER(TOP_LAYER, "sge_gdi_ctx_class_destroy");

   if (!pst || !*pst) {
      DRETURN_VOID;
   }


   sge_gdi_ctx_destroy((*pst)->sge_gdi_ctx_handle);
   FREE(*pst);
   *pst = NULL;

   DRETURN_VOID;
}
