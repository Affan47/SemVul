zxid_get_at(zxid_conf* cf, zxid_ses* ses, char* atname, int ix, int apply_map)
{
  struct zxid_attr* at;
  struct zxid_attr* av;
  if (!cf || !ses || !atname) {
    ERR("Missing args cf=%p ses=%p atname=%p", cf, ses, atname);
    return 0;
  }
  for (at = ses->at; at; at = at->n) {
    if (!strcmp(at->name, atname)) {
      for (av = at; av && ix; --ix, av = av->nv) ;
      if (av) {
	if (apply_map) {
	  return zx_dup_str(cf->ctx, at->val);
	} else
	  return zx_dup_str(cf->ctx, at->val);
      }
    }
  }
  return 0;
}
