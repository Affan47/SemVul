propval_as_string(struct propval *pv, char *buf, int buflen)
{
  int count = 0;

  fc_assert_ret_val(NULL != pv, 0);
  fc_assert_ret_val(0 < buflen, 0);

  switch (pv->valtype) {
  case VALTYPE_NONE:
    buf[0] = '\0';
    return 0;

  case VALTYPE_INT:
    return fc_snprintf(buf, buflen, "%d", pv->data.v_int);

  case VALTYPE_BOOL:
    return fc_snprintf(buf, buflen, "%s",
                       pv->data.v_bool ? _("TRUE") : _("FALSE"));

  case VALTYPE_NATION:
    return fc_snprintf(buf, buflen, "%s",
                       nation_adjective_translation(pv->data.v_nation));

  case VALTYPE_BUILT_ARRAY:
    {
      int great_wonder_count = 0, small_wonder_count = 0, building_count = 0;
      int id;

      improvement_iterate(pimprove) {
        id = improvement_index(pimprove);
        if (pv->data.v_built[id].turn < 0) {
          continue;
        }
        if (is_great_wonder(pimprove)) {
          great_wonder_count++;
        } else if (is_small_wonder(pimprove)) {
          small_wonder_count++;
        } else {
          building_count++;
        }
      } improvement_iterate_end;


      return fc_snprintf(buf, buflen, _("%db %ds %dW"),
                         building_count, small_wonder_count,
                         great_wonder_count);
    }

  case VALTYPE_INVENTIONS_ARRAY:
    advance_index_iterate(A_FIRST, tech) {
      if (pv->data.v_inventions[tech]) {
        count++;
      }
    } advance_index_iterate_end;

    return fc_snprintf(buf, buflen, _("%d known"), count);

  case VALTYPE_BV_SPECIAL:
    tile_special_type_iterate(spe) {
      if (BV_ISSET(pv->data.v_bv_special, spe)) {
        count++;
      }
    } tile_special_type_iterate_end;


    return fc_snprintf(buf, buflen, _("%d present"), count);

  case VALTYPE_BV_BASES:
    base_type_iterate(pbase) {
      if (BV_ISSET(pv->data.v_bv_bases, base_number(pbase))) {
        count++;
      }
    } base_type_iterate_end;
    return fc_snprintf(buf, buflen, _("%d present"), count);

  case VALTYPE_NATION_HASH:
    count = nation_hash_size(pv->data.v_nation_hash);
    if (0 == count) {
      return fc_snprintf(buf, buflen, "%s", _("All nations"));
    } else {
      return fc_snprintf(buf, buflen, PL_("%d nation", "%d nations",
                                          count), count);
    }

  case VALTYPE_STRING:

    count = strlen(pv->data.v_const_string);
    return fc_snprintf(buf, buflen, PL_("%d byte", "%d bytes", count),
                       count);

  case VALTYPE_PIXBUF:
  case VALTYPE_TILE_VISION_DATA:
    break;
  }

  log_error("%s(): Unhandled value type %d for property value %p.",
            __FUNCTION__, pv->valtype, pv);
  buf[0] = '\0';
  return 0;
}
