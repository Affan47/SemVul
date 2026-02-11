ipmi_sel_parse_record_event_data1 (ipmi_sel_parse_ctx_t ctx,
                                   const void *record_buf,
                                   unsigned int record_buflen,
                                   uint8_t *event_data1)
{
  struct ipmi_sel_system_event_record_data system_event_record_data;

  if (!ctx || ctx->magic != IPMI_SEL_PARSE_CTX_MAGIC)
    {
      ERR_TRACE (ipmi_sel_parse_ctx_errormsg (ctx), ipmi_sel_parse_ctx_errnum (ctx));
      return (-1);
    }

  if (!record_buf
      || !record_buflen
      || !event_data1)
    {
      SEL_PARSE_SET_ERRNUM (ctx, IPMI_SEL_PARSE_ERR_PARAMETERS);
      return (-1);
    }

  if (_parse_record_system_event_common (ctx,
                                         record_buf,
                                         record_buflen,
                                         &system_event_record_data) < 0)
    return (-1);


  *event_data1 = (system_event_record_data.offset_from_event_reading_type_code
                  | system_event_record_data.event_data3_flag << 4
                  | system_event_record_data.event_data2_flag << 6);

  ctx->errnum = IPMI_SEL_PARSE_ERR_SUCCESS;
  return (0);
}
