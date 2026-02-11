uct_init_move_ordering(struct uct_tree *tree)
{
  int pos;
  int k = 0;

  memset(tree->move_score, 0, sizeof(tree->move_score));
  for (pos = BOARDMIN; pos < BOARDMAX; pos++)
    if (ON_BOARD(pos)) {
      tree->move_ordering[k] = pos;
      tree->inverse_move_ordering[pos] = k;
      k++;
    }

  tree->num_ordered_moves = k;


  for (pos = BOARDMIN; pos < BOARDMAX; pos++) {
    if (ON_BOARD(pos)) {
      tree->move_score[pos] = (int) (10 * potential_moves[pos]) - 1;
      uct_update_move_ordering(tree, pos);
    }
  }
}
