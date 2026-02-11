ipmi_locate_pci_get_device_info (ipmi_locate_ctx_t ctx,
                                 ipmi_interface_type_t type,
                                 struct ipmi_locate_info *info)
{
  if (!ctx || ctx->magic != IPMI_LOCATE_CTX_MAGIC)
    {
      ERR_TRACE (ipmi_locate_ctx_errormsg (ctx), ipmi_locate_ctx_errnum (ctx));
      return (-1);
    }

  if (!IPMI_INTERFACE_TYPE_VALID (type) || !info)
    {
      LOCATE_SET_ERRNUM (ctx, IPMI_LOCATE_ERR_PARAMETERS);
      return (-1);
    }

  LOCATE_SET_ERRNUM (ctx, IPMI_LOCATE_ERR_SYSTEM_ERROR);
  return (-1);
}
