nextBody(int& tag, int& meshControl, int& loopC, int *loopv)
{
  int i;
  fstream& str = geometryFileStream[BODIES];
  if(step == bodies)
    {
      step = 0;
      return -1;
    }
  str >> tag >> meshControl >> loopC;
  for(i = 0; i < loopC; ++i)
    {
      str >> loopv[i];
    }
  ++step;
  return 0;
}
