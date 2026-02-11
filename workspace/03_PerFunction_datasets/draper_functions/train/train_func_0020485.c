propval_free_data(struct propval *pv)
{
  if (!pv || !pv->must_free) {
    return;
  }

  switch (pv->valtype) {
  case VALTYPE_NONE:
  case VALTYPE_INT:
  case VALTYPE_BOOL:
  case VALTYPE_BV_SPECIAL:
  case VALTYPE_BV_BASES:
  case VALTYPE_NATION:
    return;
  case VALTYPE_PIXBUF:
    g_object_unref(pv->data.v_pixbuf);
    return;
  case VALTYPE_STRING:
  case VALTYPE_BUILT_ARRAY:
  case VALTYPE_INVENTIONS_ARRAY:
  case VALTYPE_TILE_VISION_DATA:
    free(pv->data.v_pointer);
    return;
  case VALTYPE_NATION_HASH:
    nation_hash_destroy(pv->data.v_nation_hash);
    return;
  }

  log_error("%s(): Unhandled request to free data %p (type %s).",
            __FUNCTION__, pv->data.v_pointer, valtype_get_name(pv->valtype));
}
