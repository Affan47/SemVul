wonder_is_lost(const struct player *pplayer,
                    const struct impr_type *pimprove)
{
  fc_assert_ret_val(NULL != pplayer, NULL);
  fc_assert_ret_val(is_wonder(pimprove), NULL);

  return pplayer->wonders[improvement_index(pimprove)] == WONDER_LOST;
}
