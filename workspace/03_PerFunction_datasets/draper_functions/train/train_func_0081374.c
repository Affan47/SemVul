gtp_eye_data(char *s)
{
  int color = EMPTY;
  int i = -1;
  int j = -1;
  struct eye_data *e;

  if (!gtp_decode_move(s, &color, &i, &j))
    return gtp_failure("invalid color or coordinate");

  if (stackp > 0)
    return gtp_failure("eye data unavailable when stackp > 0");

  silent_examine_position(EXAMINE_DRAGONS_WITHOUT_OWL);

  gtp_start_response(GTP_SUCCESS);

  if (color == BLACK)
    e = &black_eye[POS(i, j)];
  else
    e = &white_eye[POS(i, j)];

  gtp_mprintf("origin               %m\n", I(e->origin), J(e->origin));
  gtp_mprintf("color                %C\n", e->color);
  gtp_printf("esize                %d\n", e->esize);
  gtp_printf("msize                %d\n", e->msize);
  gtp_printf("value                %s\n", eyevalue_to_string(&e->value));
  gtp_printf("marginal             %d\n", e->marginal);
  gtp_printf("neighbors            %d\n", e->neighbors);
  gtp_printf("marginal_neighbors   %d\n", e->marginal_neighbors);

  gtp_printf("\n");
  return GTP_OK;
}
