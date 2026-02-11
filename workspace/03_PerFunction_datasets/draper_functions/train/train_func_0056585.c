pick_random_player_name(const struct nation_type *pnation)
{
  const char *choice = NULL;
  int i = 0;

  nation_leader_list_iterate(nation_leaders(pnation), pleader) {
    const char *name = nation_leader_name(pleader);

    if (NULL == player_by_name(name)
        && NULL == player_by_user(name)
        && 0 == fc_rand(++i)) {
      choice = name;
    }
  } nation_leader_list_iterate_end;

  return choice;
}
