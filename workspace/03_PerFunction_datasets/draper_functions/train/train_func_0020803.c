Transform(const R2Transformation& transformation)
{

  bbox = R2null_box;
  for (int i = 0; i < npoints; i++) {
    points[i].Transform(transformation);
    bbox.Union(points[i]);
  }
}
