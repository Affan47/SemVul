gtp_does_surround(char *s)
{
  int si, sj, di, dj;
  int n;

  n = gtp_decode_coord(s, &si, &sj);
  if (n == 0)
    return gtp_failure("invalid coordinate");

  if (BOARD(si, sj) != EMPTY)
    return gtp_failure("move vertex must be empty");

  n = gtp_decode_coord(s + n, &di, &dj);
  if (n == 0)
    return gtp_failure("invalid coordinate");

  if (BOARD(di, dj) == EMPTY)
    return gtp_failure("dragon vertex must be nonempty");

  silent_examine_position(EXAMINE_DRAGONS);
  return gtp_success("%d", does_surround(POS(si, sj), POS(di, dj)));
}
