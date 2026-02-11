ipmi_sel_parse_read_sensor_type (ipmi_sel_parse_ctx_t ctx, uint8_t *sensor_type)
{
  struct ipmi_sel_system_event_record_data system_event_record_data;

  if (!ctx || ctx->magic != IPMI_SEL_PARSE_CTX_MAGIC)
    {
      ERR_TRACE (ipmi_sel_parse_ctx_errormsg (ctx), ipmi_sel_parse_ctx_errnum (ctx));
      return (-1);
    }

  if (!sensor_type)
    {
      SEL_PARSE_SET_ERRNUM (ctx, IPMI_SEL_PARSE_ERR_PARAMETERS);
      return (-1);
    }

  if (_parse_system_event_common (ctx, &system_event_record_data) < 0)
    return (-1);

  *sensor_type = system_event_record_data.sensor_type;

  ctx->errnum = IPMI_SEL_PARSE_ERR_SUCCESS;
  return (0);
}
