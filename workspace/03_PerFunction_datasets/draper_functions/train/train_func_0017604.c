_cogl_matrix_init_from_quaternion (CoglMatrix *matrix,
                                   const CoglQuaternion *quaternion)
{
  float qnorm = _COGL_QUATERNION_NORM (quaternion);
  float s = (qnorm > 0.0f) ? (2.0f / qnorm) : 0.0f;
  float xs = quaternion->x * s;
  float ys = quaternion->y * s;
  float zs = quaternion->z * s;
  float wx = quaternion->w * xs;
  float wy = quaternion->w * ys;
  float wz = quaternion->w * zs;
  float xx = quaternion->x * xs;
  float xy = quaternion->x * ys;
  float xz = quaternion->x * zs;
  float yy = quaternion->y * ys;
  float yz = quaternion->y * zs;
  float zz = quaternion->z * zs;

  matrix->xx = 1.0f - (yy + zz);
  matrix->yx = xy + wz;
  matrix->zx = xz - wy;
  matrix->xy = xy - wz;
  matrix->yy = 1.0f - (xx + zz);
  matrix->zy = yz + wx;
  matrix->xz = xz + wy;
  matrix->yz = yz - wx;
  matrix->zz = 1.0f - (xx + yy);
  matrix->xw = matrix->yw = matrix->zw = 0.0f;
  matrix->wx = matrix->wy = matrix->wz = 0.0f;
  matrix->ww = 1.0f;

  matrix->flags = (MAT_FLAG_GENERAL | MAT_DIRTY_ALL);
}
