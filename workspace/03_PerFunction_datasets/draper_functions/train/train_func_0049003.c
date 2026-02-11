comp_rules (struct board *board, short p1, short p2)
{
  short way, c1, c2;

  c1 = board->solution[p1]->solname - 1;
  c2 = board->solution[p2]->solname - 1;

  way = rulecombo[c1][c2];

  if (way & 9) {
    board->rule[0]++;
    if (overlap (board, p1, p2))
      return NO;
  }

  if (way & 2) {
    board->rule[1]++;
    if (claimeven_below (board, p1, p2))
      return NO;
  }

  if (way & 4) {
    board->rule[2]++;
    if (!column_wdoe (board, p1, p2))
      return NO;
  }

  return YES;
}
