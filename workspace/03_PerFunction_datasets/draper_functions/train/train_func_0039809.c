ecore_imf_context_input_panel_enabled_set(Ecore_IMF_Context *ctx,
                                           Eina_Bool enabled)
{
   if (!ECORE_MAGIC_CHECK(ctx, ECORE_MAGIC_CONTEXT))
     {
        ECORE_MAGIC_FAIL(ctx, ECORE_MAGIC_CONTEXT,
                         "ecore_imf_context_input_panel_enabled_set");
        return;
     }

   ctx->input_panel_enabled = enabled;
}
