city_add_improvement(struct city *pcity,
			  const struct impr_type *pimprove)
{
  pcity->built[improvement_index(pimprove)].turn = game.info.turn;

  if (is_server() && is_wonder(pimprove)) {

    wonder_built(pcity, pimprove);
  }
}
