lens_cubic_interpolate (gfloat  *src,
                        gfloat  *dst,
                        gdouble  dx,
                        gdouble  dy,
                        gdouble  brighten)
{
  gfloat um1, u, up1, up2;
  gfloat vm1, v, vp1, vp2;
  gint   c, row_stride = 16;
  gfloat verts[16];

  um1 = ((-0.5 * dx + 1.0) * dx - 0.5) * dx;
  u = (1.5 * dx - 2.5) * dx * dx + 1.0;
  up1 = ((-1.5 * dx + 2.0) * dx + 0.5) * dx;
  up2 = (0.5 * dx - 0.5) * dx * dx;

  vm1 = ((-0.5 * dy + 1.0) * dy - 0.5) * dy;
  v = (1.5 * dy - 2.5) * dy * dy + 1.0;
  vp1 = ((-1.5 * dy + 2.0) * dy + 0.5) * dy;
  vp2 = (0.5 * dy - 0.5) * dy * dy;


  for (c = 0; c < 4 * 4; ++c)
    {
      verts[c] = vm1 * src[c] + v * src[c+row_stride] +
        vp1 * src[c+row_stride*2] + vp2 * src[c+row_stride*3];
    }

  for (c = 0; c < 4; ++c)
    {
      gfloat result;

      result = um1 * verts[c] + u * verts[c+4] +
        up1 * verts[c+4*2] + up2 * verts[c+4*3];

      result *= brighten;

      dst[c] = CLAMP (result, 0.0, 1.0);
    }

}
