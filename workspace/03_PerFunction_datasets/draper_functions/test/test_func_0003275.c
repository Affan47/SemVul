firstpass_end_element_handler (GMarkupParseContext *context,
			       const gchar         *element_name,
			       gpointer             user_data,
			       GError             **error)
{
  ParseContext *ctx = user_data;
  if (strcmp (element_name, "alias") == 0)
    {
      state_switch (ctx, STATE_NAMESPACE);
      g_free (ctx->current_alias);
      ctx->current_alias = NULL;
    }
  else if (strcmp (element_name, "type") == 0 && ctx->state == STATE_TYPE)
    state_switch (ctx, ctx->prev_state);
}
