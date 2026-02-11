nation_by_number(const Nation_type_id nation)
{
  if (nation < 0 || nation >= game.control.nation_count) {
    return NULL;
  }
  return nations + nation;
}
