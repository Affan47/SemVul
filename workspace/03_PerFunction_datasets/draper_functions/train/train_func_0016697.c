tdc_plr_get(struct player *plr,
                                                 int tindex)
{
  struct ai_plr *ai = ai_plr_data_get(plr);

  fc_assert_ret_val(ai != NULL, NULL);
  fc_assert_ret_val(ai->settler != NULL, NULL);
  fc_assert_ret_val(ai->settler->tdc_hash != NULL, NULL);

  struct tile_data_cache *ptdc;

  tile_data_cache_hash_lookup(ai->settler->tdc_hash, tindex, &ptdc);

  if (!ptdc) {
#ifdef DEBUG
    ai->settler->cache.miss++;
#endif
    return NULL;
  } else if (ptdc->turn != game.info.turn) {
#ifdef DEBUG
    ai->settler->cache.old++;
#endif
    return NULL;
  } else {
#ifdef DEBUG
    ai->settler->cache.hit++;
#endif
    return ptdc;
  }
}
