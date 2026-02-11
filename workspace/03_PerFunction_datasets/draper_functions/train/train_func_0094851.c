eio_get_geometry_body
  (int& tag, int& meshControl, int& loopC,
   int *loops,
   int& info)
{
  if(geometryAgent->nextBody(tag, meshControl, loopC, loops) != -1)
    info = 0;
  else
    info = -1;
}
