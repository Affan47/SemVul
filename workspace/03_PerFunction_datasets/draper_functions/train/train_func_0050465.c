zxid_parse_meta(zxid_conf* cf, char** md, char* lim)
{
  zxid_entity* ee;
  zxid_entity* ent;
  struct zx_md_EntityDescriptor_s* ed;
  struct zx_root_s* r;

  r = zx_dec_zx_root(cf->ctx, lim-*md, *md, "parse meta");
  *md = (char*)cf->ctx->p;
  if (!r)
    return 0;
  if (r->EntityDescriptor) {
    ed = r->EntityDescriptor;
    ZX_FREE(cf->ctx, r);
    return zxid_mk_ent(cf, ed);
  } else if (r->EntitiesDescriptor) {
    if (!r->EntitiesDescriptor->EntityDescriptor)
      goto bad_md;
    ee = 0;
    for (ed = r->EntitiesDescriptor->EntityDescriptor;
	 ed;
	 ed = (struct zx_md_EntityDescriptor_s*)ZX_NEXT(ed)) {
      if (ed->gg.g.tok != zx_md_EntityDescriptor_ELEM)
	continue;
      ent = zxid_mk_ent(cf, ed);
      ent->n = ee;
      ee = ent;
    }
    ZX_FREE(cf->ctx, r->EntitiesDescriptor);
    ZX_FREE(cf->ctx, r);
    return ee;
  }
 bad_md:
  ERR("Bad metadata. EntityDescriptor could not be found or was corrupt. MD(%.*s) %d chars parsed.", ((int)(lim-cf->ctx->bas)), cf->ctx->bas, ((int)(*md - cf->ctx->bas)));
  zxlog(cf, 0, 0, 0, 0, 0, 0, 0, "N", "B", "BADMD", 0, "chars_parsed(%d)", ((int)(*md - cf->ctx->bas)));
  zx_free_elem(cf->ctx, &r->gg, 0);
  return 0;
}
