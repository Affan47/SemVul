write_node(int& tag, int& type, double *coord, int& partC, int *partsH)
{
  fstream& str = meshFileStream[NODES];
  fstream& str2 = meshFileStream[SHARED];

  str << tag << ' ' << type << ' ';

  str.setf(std::ios::scientific);
  str.precision(16);

  str << coord[0] << ' ' << coord[1] << ' ' << coord[2] << std::endl;
  if(partC > 1)
    {
      int i;
      str2 << tag << ' ' << partC << ' ';
      for(i = 0; i < partC; ++i)
	{
	  str2 << partsH[i] << ' ';
	}
      str2 << std::endl;
    }
  return 0;
}
