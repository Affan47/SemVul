property_page_add_objbinds_from_tile(struct property_page *pp,
                                                 const struct tile *ptile)
{

  if (!pp || !ptile) {
    return;
  }

  switch (property_page_get_objtype(pp)) {
  case OBJTYPE_TILE:
    property_page_add_objbind(pp, (gpointer) ptile);
    return;

  case OBJTYPE_STARTPOS:
    {
      struct startpos *psp = map_startpos_get(ptile);

      if (NULL != psp) {
        property_page_add_objbind(pp, map_startpos_get(ptile));
      }
    }
    return;

  case OBJTYPE_UNIT:
    unit_list_iterate(ptile->units, punit) {
      property_page_add_objbind(pp, punit);
    } unit_list_iterate_end;
    return;

  case OBJTYPE_CITY:
    if (tile_city(ptile)) {
      property_page_add_objbind(pp, tile_city(ptile));
    }
    return;

  case OBJTYPE_PLAYER:
  case OBJTYPE_GAME:
    return;

  case NUM_OBJTYPES:
    break;
  }

  log_error("%s(): Unhandled page object type %s (nb %d).", __FUNCTION__,
            objtype_get_name(property_page_get_objtype(pp)),
            property_page_get_objtype(pp));
}
