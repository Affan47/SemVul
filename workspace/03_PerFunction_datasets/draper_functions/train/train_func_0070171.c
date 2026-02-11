centry_list_get_via_gdi(sge_gdi_ctx_class_t *ctx, lList **answer_list)
{
   lList *ret = NULL;
   lList *gdi_answer_list = NULL;
   lEnumeration *what = NULL;

   DENTER(TOP_LAYER, "centry_list_get_via_gdi");
   what = lWhat("%T(ALL)", CE_Type);
   gdi_answer_list = ctx->gdi(ctx, SGE_CE_LIST, SGE_GDI_GET,
                             &ret, NULL, what);
   lFreeWhat(&what);

   if (answer_list_has_error(&gdi_answer_list)) {
      answer_list_replace(answer_list, &gdi_answer_list);
   }

   centry_list_sort(ret);

   lFreeList(&gdi_answer_list);

   DRETURN(ret);
}
