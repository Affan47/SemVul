_cogl_matrix_transform_points_f2 (const CoglMatrix *matrix,
                                  size_t stride_in,
                                  const void *points_in,
                                  size_t stride_out,
                                  void *points_out,
                                  int n_points)
{
  int i;

  for (i = 0; i < n_points; i++)
    {
      Point2f p = *(Point2f *)((uint8_t *)points_in + i * stride_in);
      Point3f *o = (Point3f *)((uint8_t *)points_out + i * stride_out);

      o->x = matrix->xx * p.x + matrix->xy * p.y + matrix->xw;
      o->y = matrix->yx * p.x + matrix->yy * p.y + matrix->yw;
      o->z = matrix->zx * p.x + matrix->zy * p.y + matrix->zw;
    }
}
