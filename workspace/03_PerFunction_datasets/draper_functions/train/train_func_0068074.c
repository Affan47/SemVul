player_researches_init(void)
{
  int i;


  fc_assert(ARRAY_SIZE(research_array) >= team_slot_count());
  fc_assert(ARRAY_SIZE(research_array) >= player_slot_count());

  memset(research_array, 0, sizeof(*research_array));
  for (i = 0; i < ARRAY_SIZE(research_array); i++) {
    research_array[i].tech_goal = A_UNSET;
    research_array[i].researching = A_UNSET;
    research_array[i].researching_saved = A_UNKNOWN;
    research_array[i].future_tech = 0;
  }
}
