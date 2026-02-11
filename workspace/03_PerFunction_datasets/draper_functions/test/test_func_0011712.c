analyze_false_eye_territory(void)
{
  int pos;
  int color;
  int eye_color;
  struct eye_data *eye;
  int k;

  for (pos = BOARDMIN; pos < BOARDMAX; pos++) {
    if (!ON_BOARD(pos))
      continue;

    false_eye_territory[pos] = 0;


    if (half_eye[pos].type == 0)
      continue;


    if (white_eye[pos].color == WHITE) {
      color = WHITE;
      eye_color = WHITE;
      eye = white_eye;
    }
    else if (black_eye[pos].color == BLACK) {
      color = BLACK;
      eye_color = BLACK;
      eye = black_eye;
    }
    else
      continue;


    for (k = 0; k < 4; k++)
      if (ON_BOARD(pos + delta[k])
	  && board[pos + delta[k]] != color
	  && eye[pos + delta[k]].color != eye_color)
	break;

    if (k < 4)
      continue;


    for (k = 0; k < 4; k++)
      if (ON_BOARD(pos + delta[k])
	  && board[pos + delta[k]] == color
	  && !connected_to_eye(pos, pos + delta[k], color, eye_color, eye))
	break;

    if (k == 4) {
      false_eye_territory[pos] = 1;
      if (0)
	gprintf("False eye territory at %1m\n", pos);
    }
  }


  for (pos = BOARDMIN; pos < BOARDMAX; pos++)
    if (ON_BOARD(pos))
      forced_backfilling_moves[pos] = 0;
}
