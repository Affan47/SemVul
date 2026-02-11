gtp_surround_map(char *s)
{
  int di, dj, mi, mj;
  int n;

  n = gtp_decode_coord(s, &di, &dj);
  if (n == 0)
    return gtp_failure("invalid coordinate");

  if (BOARD(di, dj) == EMPTY)
    return gtp_failure("dragon vertex must not be empty");

  n = gtp_decode_coord(s + n, &mi, &mj);
  if (n == 0)
    return gtp_failure("invalid coordinate");

  silent_examine_position(EXAMINE_DRAGONS);
  return gtp_success("%d", surround_map(POS(di, dj), POS(mi, mj)));
}
