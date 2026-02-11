sgf_trace(const char *func, int str, int move, int result,
	  const char *message)
{
  char buf[100];

  sprintf(buf, "%s %c%d: ", func, J(str) + 'A' + (J(str) >= 8),
	  board_size - I(str));

  if (result == 0)
    sprintf(buf + strlen(buf), "0");
  else if (ON_BOARD(move))
    sprintf(buf + strlen(buf), "%s %c%d", result_to_string(result),
	    J(move) + 'A' + (J(move) >= 8),
	    board_size - I(move));
  else if (is_pass(move))
    sprintf(buf + strlen(buf), "%s PASS", result_to_string(result));
  else
    sprintf(buf + strlen(buf), "%s [%d]", result_to_string(result), move);

  if (message)
    sprintf(buf + strlen(buf), " (%s)", message);

  sgftreeAddComment(sgf_dumptree, buf);
}
