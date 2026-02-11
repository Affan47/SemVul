add_owl_uncertain_defense_move(int pos, int dr)
{
  dr = dragon[dr].origin;
  ASSERT_ON_BOARD1(dr);
  add_move_reason(pos, UNCERTAIN_OWL_DEFENSE, dragon[dr].origin);
}
