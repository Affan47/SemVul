pplayer_can_make_treaty(const struct player *p1,
                                         const struct player *p2,
                                         enum diplstate_type treaty)
{
  enum diplstate_type existing = player_diplstate_get(p1, p2)->type;

  if (p1 == p2) {
    return DIPL_ERROR;
  }
  if (get_player_bonus(p1, EFT_NO_DIPLOMACY)
      || get_player_bonus(p2, EFT_NO_DIPLOMACY)) {
    return DIPL_ERROR;
  }
  if (treaty == DS_WAR
      || treaty == DS_NO_CONTACT
      || treaty == DS_ARMISTICE
      || treaty == DS_TEAM
      || treaty == DS_LAST) {
    return DIPL_ERROR;
  }
  if (treaty == DS_CEASEFIRE && existing != DS_WAR) {
    return DIPL_ERROR;
  }
  if (treaty == DS_PEACE
      && (existing != DS_WAR && existing != DS_CEASEFIRE)) {
    return DIPL_ERROR;
  }
  if (treaty == DS_ALLIANCE) {
    if (!is_valid_alliance(p1, p2)) {

      return DIPL_ALLIANCE_PROBLEM_US;
    } else if (!is_valid_alliance(p2, p1)) {

      return DIPL_ALLIANCE_PROBLEM_THEM;
    }
  }

  if (treaty == existing) {
    return DIPL_ERROR;
  }
  return DIPL_OK;
}
