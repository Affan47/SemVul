qh_vertexsubset(setT *vertexsetA, setT *vertexsetB) {
  vertexT **vertexA= (vertexT **) SETaddr_(vertexsetA, vertexT);
  vertexT **vertexB= (vertexT **) SETaddr_(vertexsetB, vertexT);

  while (True) {
    if (!*vertexA)
      return True;
    if (!*vertexB)
      return False;
    if ((*vertexA)->id > (*vertexB)->id)
      return False;
    if (*vertexA  == *vertexB)
      vertexA++;
    vertexB++;
  }
}
