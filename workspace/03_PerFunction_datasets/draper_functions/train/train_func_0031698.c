setf_color (gfloat      *workp,
            gfloat      *dummy,
            guchar      *sourcep)
{
  gint val = rintf (*workp);
  *sourcep = CLAMP0255 (val);
}
