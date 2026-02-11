ipmi_lan_2_0_cmd (ipmi_ctx_t ctx,
                  fiid_obj_t obj_cmd_rq,
                  fiid_obj_t obj_cmd_rs)
{
  uint8_t payload_authenticated;
  uint8_t payload_encrypted;

  if (!ctx || ctx->magic != IPMI_CTX_MAGIC)
    {
      ERR_TRACE (ipmi_ctx_errormsg (ctx), ipmi_ctx_errnum (ctx));
      return (-1);
    }

  if (ctx->type != IPMI_DEVICE_LAN_2_0)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_DEVICE_NOT_OPEN);
      return (-1);
    }

  if (!ctx->io.outofband.sockfd)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_DEVICE_NOT_OPEN);
      return (-1);
    }

  if (!fiid_obj_valid (obj_cmd_rq)
      || !fiid_obj_valid (obj_cmd_rs))
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_PARAMETERS);
      return (-1);
    }

  if (FIID_OBJ_PACKET_VALID (obj_cmd_rq) < 0)
    {
      API_FIID_OBJECT_ERROR_TO_API_ERRNUM (ctx, obj_cmd_rq);
      return (-1);
    }

  if (ctx->type != IPMI_DEVICE_LAN_2_0)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_INTERNAL_ERROR);
      return (-1);
    }

  ipmi_lan_2_0_cmd_get_session_parameters (ctx,
                                           &payload_authenticated,
                                           &payload_encrypted);

  return (ipmi_lan_2_0_cmd_wrapper (ctx,
                                    0,
                                    ctx->lun,
                                    ctx->net_fn,
                                    IPMI_PAYLOAD_TYPE_IPMI,
                                    payload_authenticated,
                                    payload_encrypted,
                                    NULL,
                                    &(ctx->io.outofband.session_sequence_number),
                                    ctx->io.outofband.managed_system_session_id,
                                    &(ctx->io.outofband.rq_seq),
                                    ctx->io.outofband.authentication_algorithm,
                                    ctx->io.outofband.integrity_algorithm,
                                    ctx->io.outofband.confidentiality_algorithm,
                                    ctx->io.outofband.integrity_key_ptr,
                                    ctx->io.outofband.integrity_key_len,
                                    ctx->io.outofband.confidentiality_key_ptr,
                                    ctx->io.outofband.confidentiality_key_len,
                                    strlen (ctx->io.outofband.password) ? ctx->io.outofband.password : NULL,
                                    strlen (ctx->io.outofband.password),
                                    obj_cmd_rq,
                                    obj_cmd_rs));
}
