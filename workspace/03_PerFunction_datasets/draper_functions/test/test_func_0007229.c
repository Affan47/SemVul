zxid_map_val(zxid_conf* cf, zxid_ses* ses, zxid_entity* meta, struct zxid_map* map, const char* atname, const char* val) {
  return zxid_map_val_ss(cf, ses, meta, map, atname, zx_dup_str(cf->ctx, STRNULLCHK(val)));
}
