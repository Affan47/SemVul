owl_find_relevant_eyespaces(struct local_owl_data *owl,
			    int mw[BOARDMAX], int mz[BOARDMAX])
{
  int pos;
  int eye_color;
  int k;
  struct eye_data *eye = owl->my_eye;

  if (owl->color == WHITE)
    eye_color = WHITE;
  else
    eye_color = BLACK;

  memset(mw, 0, BOARDMAX * sizeof(mw[0]));
  memset(mz, 0, BOARDMAX * sizeof(mz[0]));
  for (pos = BOARDMIN; pos < BOARDMAX; pos++) {
    if (board[pos] == owl->color) {
      for (k = 0; k < 8; k++) {
	int pos2 = pos + delta[k];
	if (ON_BOARD(pos2)
	    && eye[pos2].color == eye_color
	    && !eye[pos2].marginal) {
	  if (owl->goal[pos])
	    mw[eye[pos2].origin]++;
	  else
	    mz[eye[pos2].origin]++;
	}
      }
    }
  }
}
