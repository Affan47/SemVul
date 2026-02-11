_get_sel_entry (ipmi_sel_parse_ctx_t ctx,
                fiid_obj_t obj_cmd_rs,
                uint16_t *reservation_id,
                int *reservation_id_initialized,
                uint16_t record_id)
{
  unsigned int reservation_id_retry_count = 0;
  unsigned int reservation_canceled = 0;
  unsigned int is_insufficient_privilege_level = 0;
  int rv = -1;

  assert (ctx);
  assert (ctx->magic == IPMI_SEL_PARSE_CTX_MAGIC);
  assert (ctx->ipmi_ctx);
  assert (fiid_obj_valid (obj_cmd_rs) == 1);
  assert (fiid_obj_template_compare (obj_cmd_rs, tmpl_cmd_get_sel_entry_rs) == 1);
  assert (reservation_id);


  while (1)
    {
      if (!(*reservation_id_initialized) || reservation_canceled)
        {
          if (sel_parse_get_reservation_id (ctx, reservation_id, &is_insufficient_privilege_level) < 0)
            {


              if (is_insufficient_privilege_level)
                (*reservation_id) = 0;
              else
                goto cleanup;
            }
          (*reservation_id_initialized)++;
        }

      if (ipmi_cmd_get_sel_entry (ctx->ipmi_ctx,
                                  (*reservation_id),
                                  record_id,
                                  0,
                                  IPMI_SEL_READ_ENTIRE_RECORD_BYTES_TO_READ,
                                  obj_cmd_rs) < 0)
        {
          if (ipmi_ctx_errnum (ctx->ipmi_ctx) == IPMI_ERR_BAD_COMPLETION_CODE
              && ipmi_check_completion_code (obj_cmd_rs,
                                             IPMI_COMP_CODE_RESERVATION_CANCELLED) == 1)
            {
              reservation_id_retry_count++;
              reservation_canceled++;
              (*reservation_id_initialized) = 0;

              if (reservation_id_retry_count > IPMI_SEL_PARSE_RESERVATION_ID_RETRY)
                {
                  SEL_PARSE_SET_ERRNUM (ctx, IPMI_SEL_PARSE_ERR_IPMI_ERROR);
                  goto cleanup;
                }

              continue;
            }
          else
            {
              SEL_PARSE_SET_ERRNUM (ctx, IPMI_SEL_PARSE_ERR_IPMI_ERROR);
              goto cleanup;
            }
        }

      break;
    }

  rv = 0;
 cleanup:
  return (rv);
}
