handle_city_worklist(struct player *pplayer, int city_id,
                          const struct worklist *worklist)
{
  struct city *pcity = player_city_by_number(pplayer, city_id);

  if (!pcity) {
    return;
  }

  worklist_copy(&pcity->worklist, worklist);

  send_city_info(pplayer, pcity);
}
