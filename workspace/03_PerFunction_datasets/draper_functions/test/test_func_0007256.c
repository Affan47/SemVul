ipmi_cmd_set_lan_configuration_parameters_authentication_type_enables (ipmi_ctx_t ctx,
                                                                       uint8_t channel_number,
                                                                       uint8_t callback_level_none,
                                                                       uint8_t callback_level_md2,
                                                                       uint8_t callback_level_md5,
                                                                       uint8_t callback_level_straight_password,
                                                                       uint8_t callback_level_oem_proprietary,
                                                                       uint8_t user_level_none,
                                                                       uint8_t user_level_md2,
                                                                       uint8_t user_level_md5,
                                                                       uint8_t user_level_straight_password,
                                                                       uint8_t user_level_oem_proprietary,
                                                                       uint8_t operator_level_none,
                                                                       uint8_t operator_level_md2,
                                                                       uint8_t operator_level_md5,
                                                                       uint8_t operator_level_straight_password,
                                                                       uint8_t operator_level_oem_proprietary,
                                                                       uint8_t admin_level_none,
                                                                       uint8_t admin_level_md2,
                                                                       uint8_t admin_level_md5,
                                                                       uint8_t admin_level_straight_password,
                                                                       uint8_t admin_level_oem_proprietary,
                                                                       uint8_t oem_level_none,
                                                                       uint8_t oem_level_md2,
                                                                       uint8_t oem_level_md5,
                                                                       uint8_t oem_level_straight_password,
                                                                       uint8_t oem_level_oem_proprietary,
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
                                 tmpl_cmd_set_lan_configuration_parameters_rs) < 0)
    {
      API_FIID_OBJECT_ERROR_TO_API_ERRNUM (ctx, obj_cmd_rs);
      return (-1);
    }

  if (!(obj_cmd_rq = fiid_obj_create (tmpl_cmd_set_lan_configuration_parameters_authentication_type_enables_rq)))
    {
      API_ERRNO_TO_API_ERRNUM (ctx, errno);
      goto cleanup;
    }

  if (fill_cmd_set_lan_configuration_parameters_authentication_type_enables (channel_number,
                                                                             callback_level_none,
                                                                             callback_level_md2,
                                                                             callback_level_md5,
                                                                             callback_level_straight_password,
                                                                             callback_level_oem_proprietary,
                                                                             user_level_none,
                                                                             user_level_md2,
                                                                             user_level_md5,
                                                                             user_level_straight_password,
                                                                             user_level_oem_proprietary,
                                                                             operator_level_none,
                                                                             operator_level_md2,
                                                                             operator_level_md5,
                                                                             operator_level_straight_password,
                                                                             operator_level_oem_proprietary,
                                                                             admin_level_none,
                                                                             admin_level_md2,
                                                                             admin_level_md5,
                                                                             admin_level_straight_password,
                                                                             admin_level_oem_proprietary,
                                                                             oem_level_none,
                                                                             oem_level_md2,
                                                                             oem_level_md5,
                                                                             oem_level_straight_password,
                                                                             oem_level_oem_proprietary,
                                                                             obj_cmd_rq) < 0)
    {
      API_ERRNO_TO_API_ERRNUM (ctx, errno);
      goto cleanup;
    }

  if (api_ipmi_cmd (ctx,
                    IPMI_BMC_IPMB_LUN_BMC,
                    IPMI_NET_FN_TRANSPORT_RQ,
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
