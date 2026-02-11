fattal02_prolongate (const gfloat        *input,
                     const GeglRectangle *extent_i,
                     gfloat              *output,
                     const GeglRectangle *extent_o)
{
  gfloat dx = (gfloat)extent_i->width  / (gfloat)extent_o->width,
         dy = (gfloat)extent_i->height / (gfloat)extent_o->height;

  const guint outRows = extent_o->height,
              outCols = extent_o->width;

  const gfloat inRows = extent_i->height,
               inCols = extent_i->width;

  const float filterSize = 1;

  gfloat sx, sy;
  guint   x,  y;

  for (y = 0, sy = -dy / 2; y < outRows; ++y, sy += dy)
    {
      for (x = 0, sx = -dx / 2; x < outCols; ++x, sx += dx )
        {
          gfloat pixVal = 0;
          gfloat weight = 0;
          gfloat ix, iy;

          for (ix  = MAX (0, ceilf (sx - filterSize));
               ix <= MIN (floorf (sx + filterSize), inCols - 1);
               ++ix)
            {
              for (iy  = MAX (0, ceilf (sy - filterSize));
                   iy <= MIN (floorf (sy + filterSize), inRows - 1);
                   ++iy)
                {
                  const gfloat fx   = fabs (sx - ix),
                               fy   = fabs (sy - iy),
                               fval = (1 - fx) * (1 - fy);

                  pixVal += input[(guint)ix + (guint)iy * (guint)inCols] * fval;
                  weight += fval;
                }
            }

          g_return_if_fail (weight != 0);

          output [x + y * outCols] = pixVal / weight;
        }
    }
}
