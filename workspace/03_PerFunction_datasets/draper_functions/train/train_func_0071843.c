sge_execd_register_at_qmaster(sge_gdi_ctx_class_t *ctx, bool is_restart) {
   int return_value = 0;
   static int sge_last_register_error_flag = 0;
   lList *alp = NULL;


   const char *master_host = ctx->get_master(ctx, is_restart);

   DENTER(TOP_LAYER, "sge_execd_register_at_qmaster");


   if (master_host != NULL && ctx->is_alive(ctx) == CL_RETVAL_OK) {
      lList *hlp = lCreateList("exechost starting", EH_Type);
      lListElem *hep = lCreateElem(EH_Type);
      lSetUlong(hep, EH_featureset_id, feature_get_active_featureset_id());
      lAppendElem(hlp, hep);


      DPRINTF(("*****  Register at qmaster   *****\n"));
      if (!is_restart) {


         alp = ctx->gdi(ctx, SGE_EH_LIST, SGE_GDI_ADD, &hlp, NULL, NULL);
      } else {


         alp = ctx->gdi(ctx, SGE_EH_LIST, SGE_GDI_ADD | SGE_GDI_EXECD_RESTART,
                        &hlp, NULL, NULL);
      }
      lFreeList(&hlp);
   } else {
      DPRINTF(("*****  Register at qmaster - qmaster not alive!  *****\n"));
   }

   if (alp == NULL) {
      if (sge_last_register_error_flag == 0) {
         WARNING((SGE_EVENT, MSG_COM_CANTREGISTER_SS, master_host?master_host:"", MSG_COM_ERROR));
         sge_last_register_error_flag = 1;
      }
      return_value = 1;
   } else {
      lListElem *aep = lFirst(alp);
      if (lGetUlong(aep, AN_status) != STATUS_OK) {
         if (sge_last_register_error_flag == 0) {
            WARNING((SGE_EVENT, MSG_COM_CANTREGISTER_SS, master_host?master_host:"", lGetString(aep, AN_text)));
            sge_last_register_error_flag = 1;
         }
         return_value = 1;
      }
   }

   if (return_value == 0) {
      sge_last_register_error_flag = 0;
      INFO((SGE_EVENT, MSG_EXECD_REGISTERED_AT_QMASTER_S, master_host?master_host:""));
      last_qmaster_registration_time = sge_get_gmt();
   }
   lFreeList(&alp);
   DRETURN(return_value);
}
