visu_box_getCellMatrixv(VisuBox *box, double *m11, double *m12, double *m13,
                             double *m21, double *m22, double *m23,
                             double *m31, double *m32, double *m33)
{
  double m[3][3];

  g_return_if_fail(m11 && m12 && m13 && m21 && m22 && m23 && m31 && m32 && m33);

  visu_box_getCellMatrix(box, m);
  *m11 = m[0][0];
  *m12 = m[0][1];
  *m13 = m[0][2];
  *m21 = m[1][0];
  *m22 = m[1][1];
  *m23 = m[1][2];
  *m31 = m[2][0];
  *m32 = m[2][1];
  *m33 = m[2][2];
}
