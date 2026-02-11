init_connection_data(int color, const signed char goal[BOARDMAX],
    		     int target, int cutoff,
		     struct connection_data *conn, int speculative)
{
  int pos;
  signed char mark[BOARDMAX];

  memset(mark, 0, BOARDMAX);
  VALGRIND_MAKE_WRITABLE(conn, sizeof(conn));
  clear_connection_data(conn);

  for (pos = BOARDMIN; pos < BOARDMAX; pos++) {
    if (goal[pos]) {
      if (board[pos] == color) {
	int origin = find_origin(pos);

	if (!mark[origin]) {
	  add_to_start_queue(origin, FP(0.0), conn);
	  mark[origin] = 1;
	}
      }
      else if (board[pos] == EMPTY)
        add_to_start_queue(pos, FP(1.0), conn);
    }
  }

  conn->target = target;
  conn->cutoff_distance = cutoff;
  conn->speculative = speculative;
}
