gtp_does_defend(char *s)
{
  int i, j;
  int ti, tj;
  int defense_code;
  int n;

  n = gtp_decode_coord(s, &ti, &tj);
  if (n == 0)
    return gtp_failure("invalid coordinate");

  if (BOARD(ti, tj) != EMPTY)
    return gtp_failure("move vertex must be empty");

  n = gtp_decode_coord(s + n, &i, &j);
  if (n == 0)
    return gtp_failure("invalid coordinate");

  if (BOARD(i, j) == EMPTY)
    return gtp_failure("string vertex must not be empty");


  if (sgf_dumptree)
    reading_cache_clear();

  defense_code = does_defend(POS(ti, tj), POS(i, j));
  gtp_start_response(GTP_SUCCESS);
  gtp_print_code(defense_code);
  return gtp_finish_response();
}
