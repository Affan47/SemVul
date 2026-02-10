writeCoordinates(int& dim, int& coordsys, int *mapping,
				  int& symmetry,
				  double *start,
				  double *end1, double* end2)
{
  int i;
  fstream& str = modelDataFileStream[COORDINATES];
  str << dim << ' ' << coordsys << ' ';
  for(i = 0; i < 3; ++i)
    {
      str << mapping[i] << ' ';
    }
  str << std::endl;
  str << symmetry << std::endl;
  for(i = 0; i < 3; ++i)
    {
      str << start[i] << ' ';
    }
  str << std::endl;
   for(i = 0; i < 3; ++i)
    {
      str << end1[i] << ' ';
    }
  str << std::endl;
  for(i = 0; i < 3; ++i)
    {
      str << end1[i] << ' ';
    }
  str << std::endl;

  return 0;
}
