improvement_obsolete(const struct player *pplayer,
			  const struct impr_type *pimprove)
{
  if (!valid_advance(pimprove->obsolete_by)) {
    return FALSE;
  }

  if (is_great_wonder(pimprove)) {


   return game.info.global_advances[advance_index(pimprove->obsolete_by)];
  }

  return (player_invention_state(pplayer, advance_number(pimprove->obsolete_by)) == TECH_KNOWN);
}
