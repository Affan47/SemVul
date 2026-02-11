visu_box_convertReducedToXYZ(VisuBox *box, GArray *red,
				   float *x, float *y, float *z)
{
  float xyz_[3];

  g_return_if_fail(red && x && y && z && red->len == 3);

  visu_box_convertBoxCoordinatestoXYZ(box, xyz_, (float*)red->data);
  *x = xyz_[0]; *y = xyz_[1]; *z = xyz_[2];
}
