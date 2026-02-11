_normal_output_oem_data (ipmi_sel_state_data_t *state_data,
                         int record_has_manufacturer_id,
                         unsigned int flags)
{
  char outbuf[EVENT_OUTPUT_BUFLEN+1];
  int outbuf_len = 0;

  assert (state_data);
  assert (!state_data->prog_data->args->legacy_output);

  if (state_data->prog_data->args->output_oem_event_strings)
    {
      memset (outbuf, '\0', EVENT_OUTPUT_BUFLEN+1);
      if ((outbuf_len = _output_oem_event_strings (state_data,
                                                   outbuf,
                                                   EVENT_OUTPUT_BUFLEN,
                                                   flags)) < 0)
        return (-1);
    }

  if (!outbuf_len)
    {
      memset (outbuf, '\0', EVENT_OUTPUT_BUFLEN+1);
      if (state_data->prog_data->args->output_manufacturer_id
          && record_has_manufacturer_id)
        {
          if ((outbuf_len = ipmi_sel_parse_read_record_string (state_data->sel_parse_ctx,
                                                               "%m ; %o",
                                                               outbuf,
                                                               EVENT_OUTPUT_BUFLEN,
                                                               flags)) < 0)
            {
              if (_sel_parse_err_handle (state_data, "ipmi_sel_parse_read_record_string") < 0)
                return (-1);
              return (0);
            }
        }
      else
        {
          if ((outbuf_len = ipmi_sel_parse_read_record_string (state_data->sel_parse_ctx,
                                                               "%o",
                                                               outbuf,
                                                               EVENT_OUTPUT_BUFLEN,
                                                               flags)) < 0)
            {
              if (_sel_parse_err_handle (state_data, "ipmi_sel_parse_read_record_string") < 0)
                return (-1);
              return (0);
            }
        }
    }

  if (state_data->prog_data->args->comma_separated_output)
    {
      if (outbuf_len)
        pstdout_printf (state_data->pstate, ",%s", outbuf);
      else
        pstdout_printf (state_data->pstate, ",%s", EVENT_NA_STRING);
    }
  else
    {
      if (outbuf_len)
        pstdout_printf (state_data->pstate, " | %s", outbuf);
      else
        pstdout_printf (state_data->pstate, " | %s", EVENT_NA_STRING);
    }

  return (1);
}
