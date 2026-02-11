_delete_entry (ipmi_sel_state_data_t *state_data,
               uint16_t record_id,
               int ignore_missing_sel_entries)
{
  int rv = -1;

  assert (state_data);
  assert (record_id);

  if (ipmi_sel_parse_delete_sel_entry (state_data->sel_parse_ctx,
                                       record_id) < 0)
    {
      if (!(ignore_missing_sel_entries
            && (ipmi_sel_parse_ctx_errnum (state_data->sel_parse_ctx) == IPMI_SEL_PARSE_ERR_NOT_FOUND)))
        {
          pstdout_fprintf (state_data->pstate,
                           stderr,
                           "ipmi_sel_parse_delete_sel_entry: %s\n",
                           ipmi_sel_parse_ctx_errormsg (state_data->sel_parse_ctx));
          goto cleanup;
        }
    }

  rv = 0;
 cleanup:
  return (rv);
}
