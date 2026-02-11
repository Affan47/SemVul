_smbios_decode (ipmi_locate_ctx_t ctx,
                fipmiu8 *buf,
                const char *devmem,
                ipmi_interface_type_t type,
                struct ipmi_locate_info *locate_info)
{
  assert (ctx);
  assert (ctx->magic == IPMI_LOCATE_CTX_MAGIC);
  assert (devmem);
  assert (IPMI_INTERFACE_TYPE_VALID (type));
  assert (locate_info);

  if (_checksum (buf, buf[0x05]) &&
      (memcmp (buf + 0x10, "_DMI_", 5) == 0) &&
      _checksum (buf + 0x10, 0x0F))
    return (_dmi_table (ctx,
                        DWORD (buf + 0x18),
                        WORD (buf + 0x16),
                        WORD (buf + 0x1C),
                        (buf[0x06] << 8) + buf[0x07],
                        devmem,
                        type,
                        locate_info));

  return (-1);
}
