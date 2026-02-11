is_city_in_tile(const struct tile *ptile,
			    const struct city *pcity)
{
  if (pcity == NULL) {
    return tile_city(ptile) != NULL;
  } else {
    return is_city_center(pcity, ptile);
  }
}
