mantiuk06_matrix_upsample (const gint          outCols,
                           const gint          outRows,
                           const gfloat *const in,
                           gfloat       *const out)
{
  const int inRows = outRows/2;
  const int inCols = outCols/2;
  gint      x, y;


  const gfloat dx = (gfloat)inCols / ((gfloat)outCols);
  const gfloat dy = (gfloat)inRows / ((gfloat)outRows);
  const gfloat factor = 1.0f / (dx*dy);


  _OMP (omp parallel for schedule(static))
  for (y = 0; y < outRows; y++)
    {
      const gfloat sy  = y * dy;
      const gint   iy1 =      (  y   * inRows) / outRows;
      const gint   iy2 = MIN (((y+1) * inRows) / outRows, inRows-1);

      for (x = 0; x < outCols; x++)
        {
          const gfloat sx  = x * dx;
          const gint   ix1 =      (  x    * inCols) / outCols;
          const gint   ix2 =  MIN (((x+1) * inCols) / outCols, inCols-1);

          out[x + y*outCols] = (
            ((ix1+1) - sx)*((iy1+1 - sy)) * in[ix1 + iy1*inCols] +
            ((ix1+1) - sx)*(sy+dy - (iy1+1)) * in[ix1 + iy2*inCols] +
            (sx+dx - (ix1+1))*((iy1+1 - sy)) * in[ix2 + iy1*inCols] +
            (sx+dx - (ix1+1))*(sy+dx - (iy1+1)) * in[ix2 + iy2*inCols])*factor;
        }
    }
}
