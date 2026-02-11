eio_get_geometry_element
  (int& tag, int& cTag, int& meshControl,
   int& type, int& nodeC, int *nodes, int& info)
{

  if(geometryAgent->nextElement(tag, cTag, meshControl, type, nodeC, nodes) != -1)
    info = 0;
  else
    info = -1;
}
