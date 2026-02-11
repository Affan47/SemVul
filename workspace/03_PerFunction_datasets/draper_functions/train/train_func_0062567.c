ipmi_cmd_get_sensor_reading_ipmb (ipmi_ctx_t ctx,
                                  uint8_t channel_number,
                                  uint8_t slave_address,
                                  uint8_t lun,
                                  uint8_t sensor_number,
                                  fiid_obj_t obj_cmd_rs)
{
  fiid_obj_t obj_cmd_rq = NULL;
  int rv = -1;

  if (!ctx || ctx->magic != IPMI_CTX_MAGIC)
    {
      ERR_TRACE (ipmi_ctx_errormsg (ctx), ipmi_ctx_errnum (ctx));
      return (-1);
    }

  if (!fiid_obj_valid (obj_cmd_rs))
    {
      API_SET_ERRNUM (ctx, IPMI_ERR_PARAMETERS);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd_rs,
                                 tmpl_cmd_get_sensor_reading_rs) < 0)
    {
      API_FIID_OBJECT_ERROR_TO_API_ERRNUM (ctx, obj_cmd_rs);
      return (-1);
    }

  if (!(obj_cmd_rq = fiid_obj_create (tmpl_cmd_get_sensor_reading_rq)))
    {
      API_ERRNO_TO_API_ERRNUM (ctx, errno);
      goto cleanup;
    }

  if (fill_cmd_get_sensor_reading (sensor_number,
                                   obj_cmd_rq) < 0)
    {
      API_ERRNO_TO_API_ERRNUM (ctx, errno);
      goto cleanup;
    }

  if (api_ipmi_cmd_ipmb (ctx,
                         channel_number,
                         slave_address,
                         lun,
                         IPMI_NET_FN_SENSOR_EVENT_RQ,
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
