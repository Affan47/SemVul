write_element(int& tag, int& body, int& type, int *nodes, int& border)
{
  int i;
  fstream& str = meshFileStream[ELEMENTS];
  fstream& str2 = meshFileStream[BORDER];

  str << tag << ' ' << body << ' ' << type << ' ';
  if(type == 303)
    {
      for(i = 0; i < 3; ++i)
	{
	  str << nodes[i] << ' ';
	}
    }
  str << std::endl;

  if(border)
    {
      str2 << tag << std::endl;
    }
  return 0;
}
