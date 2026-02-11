add_false_eye(int pos, struct eye_data eye[BOARDMAX],
	      struct half_eye_data heye[BOARDMAX])
{
  int k;
  ASSERT1(heye[pos].type == FALSE_EYE, pos);
  DEBUG(DEBUG_EYES, "false eye found at %1m\n", pos);

  if (eye[pos].color == GRAY || eye[pos].marginal != 0)
    return;

  eye[pos].marginal = 1;
  eye[eye[pos].origin].msize++;
  for (k = 0; k < 4; k++)
    if (ON_BOARD(pos + delta[k])
	&& eye[pos + delta[k]].origin == eye[pos].origin)
      eye[pos + delta[k]].marginal_neighbors++;
  propagate_eye(eye[pos].origin, eye);
}
