vtkLinearLookupMain(double v,
                                          unsigned char *table,
                                          double maxIndex,
                                          double shift, double scale)
{
  double findx = (v + shift)*scale;


  findx = (findx > 0 ? findx : 0);
  findx = (findx < maxIndex ? findx : maxIndex);

  return &table[4*static_cast<unsigned int>(findx)];
}
