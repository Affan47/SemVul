getScaledSize(const cairo_matrix_t *matrix,
                                   int                   orig_width,
				   int                   orig_height,
				   int                  *scaledWidth,
				   int                  *scaledHeight)
{
  double xScale;
  double yScale;
  if (orig_width > orig_height)
    get_singular_values (matrix, &xScale, &yScale);
  else
    get_singular_values (matrix, &yScale, &xScale);

  int tx, tx2, ty, ty2;
  if (xScale >= 0) {
    tx = splashRound(matrix->x0 - 0.01);
    tx2 = splashRound(matrix->x0 + xScale + 0.01) - 1;
  } else {
    tx = splashRound(matrix->x0 + 0.01) - 1;
    tx2 = splashRound(matrix->x0 + xScale - 0.01);
  }
  *scaledWidth = abs(tx2 - tx) + 1;

  if (*scaledWidth == 0) {


    *scaledWidth = 1;
  }
  if (yScale >= 0) {
    ty = splashFloor(matrix->y0 + 0.01);
    ty2 = splashCeil(matrix->y0 + yScale - 0.01);
  } else {
    ty = splashCeil(matrix->y0 - 0.01);
    ty2 = splashFloor(matrix->y0 + yScale + 0.01);
  }
  *scaledHeight = abs(ty2 - ty);
  if (*scaledHeight == 0) {
    *scaledHeight = 1;
  }
}
