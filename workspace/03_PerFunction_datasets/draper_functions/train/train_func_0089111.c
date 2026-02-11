setf_alphax (gfloat     *workp,
             gfloat     *realp,
             guchar     *sourcep)
{
  gint val = rintf (255.0f * *workp / *realp);
  *sourcep = CLAMP0255 (val);
}
