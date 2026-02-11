sel_parse_get_reservation_id (ipmi_sel_parse_ctx_t ctx,
                              uint16_t *reservation_id,
                              unsigned int *is_insufficient_privilege_level)
{
  fiid_obj_t obj_cmd_rs = NULL;
  uint64_t val;
  int rv = -1;

  assert (ctx);
  assert (ctx->magic == IPMI_SEL_PARSE_CTX_MAGIC);
  assert (reservation_id);

  if (is_insufficient_privilege_level)
    (*is_insufficient_privilege_level) = 0;

  if (!(obj_cmd_rs = fiid_obj_create (tmpl_cmd_reserve_sel_rs)))
    {
      SEL_PARSE_ERRNO_TO_SEL_PARSE_ERRNUM (ctx, errno);
      goto cleanup;
    }

  if (ipmi_cmd_reserve_sel (ctx->ipmi_ctx, obj_cmd_rs) < 0)
    {


      if (ipmi_ctx_errnum (ctx->ipmi_ctx) == IPMI_ERR_BAD_COMPLETION_CODE
          && ipmi_check_completion_code (obj_cmd_rs,
                                         IPMI_COMP_CODE_INVALID_COMMAND) == 1)
        {
          *reservation_id = 0;
          goto out;
        }


      if (is_insufficient_privilege_level
          && ipmi_ctx_errnum (ctx->ipmi_ctx) == IPMI_ERR_PRIVILEGE_LEVEL_INSUFFICIENT
          && ipmi_check_completion_code (obj_cmd_rs,
                                         IPMI_COMP_CODE_INSUFFICIENT_PRIVILEGE_LEVEL) == 1)
        (*is_insufficient_privilege_level) = 1;

      SEL_PARSE_SET_ERRNUM (ctx, IPMI_SEL_PARSE_ERR_IPMI_ERROR);
      goto cleanup;
    }

  if (FIID_OBJ_GET (obj_cmd_rs,
                    "reservation_id",
                    &val) < 0)
    {
      SEL_PARSE_FIID_OBJECT_ERROR_TO_SEL_PARSE_ERRNUM (ctx, obj_cmd_rs);
      goto cleanup;
    }
  *reservation_id = val;

 out:
  rv = 0;
 cleanup:
  fiid_obj_destroy (obj_cmd_rs);
  return (rv);
}
