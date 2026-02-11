get_city_tithes_bonus(const struct city *pcity)
{
  int tithes_bonus = 0;

  if (!get_city_bonus(pcity, EFT_HAPPINESS_TO_GOLD)) {
    return 0;
  }

  tithes_bonus += get_city_bonus(pcity, EFT_MAKE_CONTENT);
  tithes_bonus += get_city_bonus(pcity, EFT_FORCE_CONTENT);

  return tithes_bonus;
}
