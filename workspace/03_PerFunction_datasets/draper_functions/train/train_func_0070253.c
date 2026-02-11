sgffile_printboard(SGFTree *tree)
{
  int i, j;
  SGFNode *node;

  gg_assert(tree);
  node = tree->lastnode;


  for (i = 0; i < board_size; i++) {
    for (j = 0; j < board_size; j++) {
      if (BOARD(i, j) == WHITE)
	sgfAddStone(node, WHITE, i, j);
    }
  }


  for (i = 0; i < board_size; i++) {
    for (j = 0; j < board_size; j++) {
      if (BOARD(i, j) == BLACK)
	sgfAddStone(node, BLACK, i, j);
    }
  }

  sgftreeSetLastNode(tree, node);
}
