write_elementConnections(int& tag, int& body, int& type, int* nodes)
{
  int i;
  fstream& str = meshFileStream[ELEMENTS];
  str << tag << ' ' << body << ' ' << type << ' ';
  int elNodes = elementNodes(type);
  for(i = 0; i < elNodes; ++i)
    {
      str << nodes[i] << ' ';
    }
  str << std::endl;
  return 0;
}
