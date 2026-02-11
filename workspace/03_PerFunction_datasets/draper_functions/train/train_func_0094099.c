cogl_matrix_equal (const void *v1, const void *v2)
{
  const CoglMatrix *a = v1;
  const CoglMatrix *b = v2;

  _COGL_RETURN_VAL_IF_FAIL (v1 != NULL, FALSE);
  _COGL_RETURN_VAL_IF_FAIL (v2 != NULL, FALSE);


  if (a->xx == b->xx &&
      a->xy == b->xy &&
      a->xz == b->xz &&
      a->xw == b->xw &&
      a->yx == b->yx &&
      a->yy == b->yy &&
      a->yz == b->yz &&
      a->yw == b->yw &&
      a->zx == b->zx &&
      a->zy == b->zy &&
      a->zz == b->zz &&
      a->zw == b->zw &&
      a->wx == b->wx &&
      a->wy == b->wy &&
      a->wz == b->wz &&
      a->ww == b->ww)
    return TRUE;
  else
    return FALSE;
}
