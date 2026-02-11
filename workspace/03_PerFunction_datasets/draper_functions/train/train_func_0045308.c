ipmi_ssif_cmd_api (ipmi_ctx_t ctx,
                   fiid_obj_t obj_cmd_rq,
                   fiid_obj_t obj_cmd_rs)
{
  uint8_t cmd = 0;
  uint8_t group_extension = 0;
  uint64_t val;
  struct timespec request, remain;
  uint8_t retry = IPMI_SSIF_RETRY_DEFAULT;

  if (!ctx || ctx->magic != IPMI_CTX_MAGIC)
    {
      ERR_TRACE (ipmi_ctx_errormsg (ctx), ipmi_ctx_errnum (ctx));
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

  if (ctx->type != IPMI_DEVICE_SSIF)
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_INTERNAL_ERROR);
      return (-1);
    }

  if (ctx->flags & IPMI_FLAGS_DEBUG_DUMP)
    {

      if (FIID_OBJ_GET (obj_cmd_rq, "cmd", &val) < 0)
        API_FIID_OBJECT_ERROR_TO_API_ERRNUM (ctx, obj_cmd_rq);
      else
        cmd = val;

      if (IPMI_NET_FN_GROUP_EXTENSION (ctx->net_fn))
        {

          if (FIID_OBJ_GET (obj_cmd_rq,
                            "group_extension_identification",
                            &val) < 0)
            API_FIID_OBJECT_ERROR_TO_API_ERRNUM (ctx, obj_cmd_rq);
          else
            group_extension = val;
        }
    }

  if (_ssif_cmd_write (ctx, cmd, group_extension, obj_cmd_rq) < 0)
    return (-1);


  if (_ssif_cmd_read (ctx, cmd, group_extension, obj_cmd_rs) < 0)
    {
      while (1)
        {
          request.tv_sec = 0;
          request.tv_nsec = IPMI_SSIF_TIMEOUT_DEFAULT;
          if (nanosleep (&request, &remain) < 0 )
            return (-1);

          if (_ssif_cmd_read (ctx, cmd, group_extension, obj_cmd_rs) < 0)
            {
              if (retry == 0)
                return (-1);

              retry--;
            }
            else
              break;
        }
    }

  return (0);
}
