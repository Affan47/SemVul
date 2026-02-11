mac_verify (gcry_mac_hd_t hd, const void *buf, size_t buflen)
{
  if (!buf || buflen == 0 || !hd->spec->ops->verify)
    return GPG_ERR_INV_ARG;

  return hd->spec->ops->verify (hd, buf, buflen);
}
