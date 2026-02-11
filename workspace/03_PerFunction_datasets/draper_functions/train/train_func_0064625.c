_ecore_imf_context_xim_use_preedit_set(Ecore_IMF_Context *ctx,
                                       Eina_Bool use_preedit)
{
   EINA_LOG_DBG("in");
#ifdef ENABLE_XIM
   Ecore_IMF_Context_Data *imf_context_data;
   imf_context_data = ecore_imf_context_data_get(ctx);
   EINA_SAFETY_ON_NULL_RETURN(imf_context_data);

   use_preedit = use_preedit != EINA_FALSE;

   if (imf_context_data->use_preedit != use_preedit)
     {
        imf_context_data->use_preedit = use_preedit;
        reinitialize_ic(ctx);
     }
#else
   (void)ctx;
   (void)use_preedit;
#endif
}
