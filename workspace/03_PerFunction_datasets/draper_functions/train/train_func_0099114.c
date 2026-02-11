replay_node(SGFNode *node, int color_to_replay, float *replay_score,
	    float *total_score)
{
  SGFProperty *sgf_prop;
  SGFProperty *move_prop = NULL;
  int color;

  int old_move;
  int new_move;

  char buf[BUFSIZE];


  for (sgf_prop = node->props; sgf_prop; sgf_prop = sgf_prop->next) {
    switch (sgf_prop->name) {
    case SGFAB:

      add_stone(get_sgfmove(sgf_prop), BLACK);
      break;
    case SGFAW:

      add_stone(get_sgfmove(sgf_prop), WHITE);
      break;
    case SGFB:
    case SGFW:
      move_prop = sgf_prop;
      break;
    }
  }


  if (!move_prop)
    return;

  old_move = get_sgfmove(move_prop);
  color = (move_prop->name == SGFW) ? WHITE : BLACK;

  if (color == color_to_replay || color_to_replay == GRAY) {
    float new_move_value = 0.0;
    float old_move_value = 0.0;


    int resign;
    new_move = genmove(color, NULL, &resign);


    if (new_move != PASS_MOVE)
      new_move_value = potential_moves[new_move];
    if (old_move != PASS_MOVE)
      old_move_value = potential_moves[old_move];


    if (new_move != old_move || !quiet) {
      mprintf("Move %d (%C): ", movenum + 1, color);

      if (resign)
	printf("GNU Go resigns ");
      else {
	mprintf("GNU Go plays %1m ", new_move);
	if (new_move != PASS_MOVE)
	  printf("(%.2f) ", new_move_value);
      }

      mprintf("- Game move %1m ", old_move);
      if (new_move != PASS_MOVE && old_move_value > 0.0)
	printf("(%.2f) ", old_move_value);
      printf("\n");

      *replay_score += new_move_value - old_move_value;
      *total_score += new_move_value;
    }

    if (new_move != old_move) {
      if (resign)
	gg_snprintf(buf, BUFSIZE, "GNU Go resigns - Game move %s (%.2f)",
		    location_to_string(old_move), old_move_value);
      else {
	gg_snprintf(buf, BUFSIZE,
		    "GNU Go plays %s (%.2f) - Game move %s (%.2f)",
		    location_to_string(new_move), new_move_value,
		    location_to_string(old_move), old_move_value);
	if (new_move != PASS_MOVE)
	  sgfCircle(node, I(new_move), J(new_move));
      }
    }
    else
      gg_snprintf(buf, BUFSIZE, "GNU Go plays the same move %s (%.2f)",
		  location_to_string(new_move), new_move_value);

    sgfAddComment(node, buf);
    sgffile_add_debuginfo(node, 0.0);
  }


  play_move(old_move, color);
}
