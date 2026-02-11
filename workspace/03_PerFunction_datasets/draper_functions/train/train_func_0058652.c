sgffile_printsgf(int color_to_play, const char *filename)
{
  SGFTree sgftree;
  int m, n;
  char pos[3];
  char str[128];
  float relative_komi;

  relative_komi = komi + black_captured - white_captured;

  sgftree_clear(&sgftree);
  sgftreeCreateHeaderNode(&sgftree, board_size, relative_komi, handicap);
  sgf_write_header(sgftree.root, 1, get_random_seed(), relative_komi,
		   handicap, get_level(), chinese_rules);
  gg_snprintf(str, 128, "GNU Go %s load and print", gg_version());
  sgfOverwriteProperty(sgftree.root, "GN", str);

  sgffile_printboard(&sgftree);

  if (color_to_play != EMPTY) {
    sgfAddProperty(sgftree.lastnode, "PL",
		   (color_to_play == WHITE ? "W" : "B"));

    for (m = 0; m < board_size; ++m)
      for (n = 0; n < board_size; ++n)
        if (BOARD(m, n) == EMPTY && !is_legal(POS(m, n), color_to_play)) {
	  gg_snprintf(pos, 3, "%c%c", 'a' + n, 'a' + m);
	  sgfAddProperty(sgftree.lastnode, "IL", pos);
	}
  }

  writesgf(sgftree.root, filename);
}
