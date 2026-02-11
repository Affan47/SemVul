really_give_tile_info_from_player_to_player(struct player *pfrom,
							struct player *pdest,
							struct tile *ptile)
{
  struct player_tile *from_tile, *dest_tile;
  if (!map_is_known_and_seen(ptile, pdest, V_MAIN)) {


    if (map_is_known_and_seen(ptile, pfrom, V_MAIN)
	|| (map_is_known(ptile, pfrom)
	    && (((map_get_player_tile(ptile, pfrom)->last_updated
		 > map_get_player_tile(ptile, pdest)->last_updated))
	        || !map_is_known(ptile, pdest)))) {
      from_tile = map_get_player_tile(ptile, pfrom);
      dest_tile = map_get_player_tile(ptile, pdest);

      map_set_known(ptile, pdest);
      dest_tile->terrain = from_tile->terrain;
      dest_tile->special = from_tile->special;
      dest_tile->resource = from_tile->resource;
      dest_tile->bases    = from_tile->bases;
      dest_tile->last_updated = from_tile->last_updated;
      send_tile_info(pdest->connections, ptile, FALSE);


      if (dest_tile->site) {
	if (!from_tile->site) {


	  reality_check_city(pdest, ptile);
	} else
	  if (from_tile->site->identity
              != dest_tile->site->identity) {


	    reality_check_city(pdest, ptile);
          }
      }


      if (from_tile->site) {
	if (!dest_tile->site) {


          dest_tile->site = vision_site_new(0, ptile, NULL);
          *dest_tile->site = *from_tile->site;
	}


	send_city_info_at_tile(pdest, pdest->connections, NULL, ptile);
      }

      city_map_update_tile_frozen(ptile);
    }
  }
}
