zxid_decrypt_newnym(zxid_conf* cf, struct zx_str* newnym, struct zx_sp_NewEncryptedID_s* encid)
{
  struct zx_str* ss;
  struct zx_root_s* r;
  if (newnym)
    return newnym;
  if (encid) {
    ss = zxenc_privkey_dec(cf, encid->EncryptedData, encid->EncryptedKey);
    r = zx_dec_zx_root(cf->ctx, ss->len, ss->s, "dec newnym");
    if (!r) {
      ERR("Failed to parse NewEncryptedID buf(%.*s)", ss->len, ss->s);
      return 0;
    }
    return ZX_GET_CONTENT(r->NewID);
  }
  ERR("Neither NewNameID nor NewEncryptedID available %d", 0);
  return 0;
}
