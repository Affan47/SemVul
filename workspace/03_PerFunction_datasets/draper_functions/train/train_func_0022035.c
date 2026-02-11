ResetDiceState(UndoScoreElement *elem) {
  gint ii;
  for (ii = 0; ii < NUMBER_OF_DICE; ii++) {
    DiceValues[ii].val = elem->DiceValues[ii];
    DiceValues[ii].sel = 0;
  }
  NumberOfRolls = elem->roll;
  ShowPlayer (elem->player, elem->field);
}
