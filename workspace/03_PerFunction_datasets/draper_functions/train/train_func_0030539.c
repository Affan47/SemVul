ipmi_cmd_enable_message_channel_receive (ipmi_ctx_t ctx,
                                         uint8_t channel_number,
                                         uint8_t channel_operation,
                                         fiid_obj_t obj_cmd_rs)
{
  fiid_obj_t obj_cmd_rq = NULL;
  int rv = -1;

  if (!ctx || ctx->magic != IPMI_CTX_MAGIC)
    {
      ERR_TRACE (ipmi_ctx_errormsg (ctx), ipmi_ctx_errnum (ctx));
      return (-1);
    }

  if (ctx->type == IPMI_DEVICE_LAN
      || ctx->type == IPMI_DEVICE_LAN_2_0)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_COMMAND_INVALID_FOR_SELECTED_INTERFACE);
      return (-1);
    }


  if (!fiid_obj_valid (obj_cmd_rs))
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_PARAMETERS);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd_rs,
                                 tmpl_cmd_enable_message_channel_receive_rs) < 0)
    {
      API_FIID_OBJECT_ERROR_TO_API_ERRNUM (ctx, obj_cmd_rs);
      return (-1);
    }

  if (!(obj_cmd_rq = fiid_obj_create (tmpl_cmd_enable_message_channel_receive_rq)))
    {
      API_ERRNO_TO_API_ERRNUM (ctx, errno);
      goto cleanup;
    }

  if (fill_cmd_enable_message_channel_receive (channel_number,
                                               channel_operation,
                                               obj_cmd_rq) < 0)
    {
      API_ERRNO_TO_API_ERRNUM (ctx, errno);
      goto cleanup;
    }

  if (api_ipmi_cmd (ctx,
                    IPMI_BMC_IPMB_LUN_BMC,
                    IPMI_NET_FN_APP_RQ,
                    obj_cmd_rq,
                    obj_cmd_rs) < 0)
    {
      ERR_TRACE (ipmi_ctx_errormsg (ctx), ipmi_ctx_errnum (ctx));
      goto cleanup;
    }

  rv = 0;
 cleanup:
  fiid_obj_destroy (obj_cmd_rq);
  return (rv);
}
