_get_sel_oem_sensor_state (ipmi_interpret_ctx_t ctx,
                           const void *record_buf,
                           unsigned int record_buflen,
                           uint8_t event_reading_type_code,
                           uint8_t sensor_type,
                           unsigned int *sel_state)
{
  char keybuf[IPMI_OEM_HASH_KEY_BUFLEN + 1];
  struct ipmi_interpret_sel_oem_sensor_config *oem_conf;

  assert (ctx);
  assert (ctx->magic == IPMI_INTERPRET_CTX_MAGIC);
  assert (record_buf);
  assert (record_buflen);
  assert (sel_state);

  memset (keybuf, '\0', IPMI_OEM_HASH_KEY_BUFLEN + 1);

  snprintf (keybuf,
            IPMI_OEM_HASH_KEY_BUFLEN,
            "%u:%u:%u:%u",
            ctx->manufacturer_id,
            ctx->product_id,
            event_reading_type_code,
            sensor_type);

  if ((oem_conf = hash_find (ctx->interpret_sel.sel_oem_sensor_config,
			     keybuf)))
    {
      unsigned int i;
      uint8_t event_direction;
      uint8_t event_data1;
      uint8_t event_data2;
      uint8_t event_data3;
      int found = 0;

      (*sel_state) = IPMI_INTERPRET_STATE_NOMINAL;

      if (ipmi_sel_parse_record_sensor_type (ctx->sel_parse_ctx,
                                             record_buf,
                                             record_buflen,
                                             &sensor_type) < 0)
        {
          INTERPRET_SEL_PARSE_CTX_ERROR_TO_INTERPRET_ERRNUM (ctx, ctx->sel_parse_ctx);
          return (-1);
        }

      if (ipmi_sel_parse_record_event_direction (ctx->sel_parse_ctx,
                                                 record_buf,
                                                 record_buflen,
                                                 &event_direction) < 0)
        {
          INTERPRET_SEL_PARSE_CTX_ERROR_TO_INTERPRET_ERRNUM (ctx, ctx->sel_parse_ctx);
          return (-1);
        }

      if (ipmi_sel_parse_record_event_data1 (ctx->sel_parse_ctx,
                                             record_buf,
                                             record_buflen,
                                             &event_data1) < 0)
        {
          INTERPRET_SEL_PARSE_CTX_ERROR_TO_INTERPRET_ERRNUM (ctx, ctx->sel_parse_ctx);
          return (-1);
        }

      if (ipmi_sel_parse_record_event_data2 (ctx->sel_parse_ctx,
                                             record_buf,
                                             record_buflen,
                                             &event_data2) < 0)
        {
          INTERPRET_SEL_PARSE_CTX_ERROR_TO_INTERPRET_ERRNUM (ctx, ctx->sel_parse_ctx);
          return (-1);
        }

      if (ipmi_sel_parse_record_event_data3 (ctx->sel_parse_ctx,
                                             record_buf,
                                             record_buflen,
                                             &event_data3) < 0)
        {
          INTERPRET_SEL_PARSE_CTX_ERROR_TO_INTERPRET_ERRNUM (ctx, ctx->sel_parse_ctx);
          return (-1);
        }

      for (i = 0; i < oem_conf->oem_sensor_data_count; i++)
	{
	  if ((oem_conf->oem_sensor_data[i].event_direction_any_flag
               || oem_conf->oem_sensor_data[i].event_direction == event_direction)
              && (oem_conf->oem_sensor_data[i].event_data1_any_flag
                  || oem_conf->oem_sensor_data[i].event_data1 == event_data1)
              && (oem_conf->oem_sensor_data[i].event_data2_any_flag
                  || oem_conf->oem_sensor_data[i].event_data2 == event_data2)
              && (oem_conf->oem_sensor_data[i].event_data3_any_flag
                  || oem_conf->oem_sensor_data[i].event_data3 == event_data3))
	    {
              if (oem_conf->oem_sensor_data[i].sel_state > (*sel_state))
                (*sel_state) = oem_conf->oem_sensor_data[i].sel_state;
              found++;
	    }
	}

      if (!found)
	(*sel_state) = IPMI_INTERPRET_STATE_UNKNOWN;
    }
  else
    (*sel_state) = IPMI_INTERPRET_STATE_UNKNOWN;

  return (0);
}
