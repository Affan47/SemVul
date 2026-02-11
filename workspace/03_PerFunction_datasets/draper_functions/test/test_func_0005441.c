nextBoundary(int& tag, int& left, int& right)
{
  fstream& str = geometryFileStream[BOUNDARIES];
  if(step == (inner + outer))
    {
      step = 0;
      return -1;
    }
  str >> tag >> left >> right;
  ++step;
  return 0;
}
