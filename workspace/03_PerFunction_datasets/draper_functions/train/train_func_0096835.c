ipmi_sel_parse_first (ipmi_sel_parse_ctx_t ctx)
{
  if (!ctx || ctx->magic != IPMI_SEL_PARSE_CTX_MAGIC)
    {
      ERR_TRACE (ipmi_sel_parse_ctx_errormsg (ctx), ipmi_sel_parse_ctx_errnum (ctx));
      return (-1);
    }

  if (!ctx->sel_entries_itr)
    {
      ctx->errnum = IPMI_SEL_PARSE_ERR_NO_SEL_ENTRIES;
      return (-1);
    }

  list_iterator_reset (ctx->sel_entries_itr);
  ctx->current_sel_entry = list_next (ctx->sel_entries_itr);
  return (0);
}
