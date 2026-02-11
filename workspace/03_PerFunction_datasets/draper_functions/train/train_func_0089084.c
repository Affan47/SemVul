convf_fill0 (gfloat     *workp,
             gfloat     *realp)
{
  if (*workp > 0.0001f &&
      *realp > 0.0001f &&
      *realp < 1.0f)
    *workp = (1.0f - *realp) / *workp;
  else
    *workp = 0.0f;
}
