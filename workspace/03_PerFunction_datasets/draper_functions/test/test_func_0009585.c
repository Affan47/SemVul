comparePolygonPoint(gconstpointer pointA, gconstpointer pointB, gpointer data)
{
  VisuPlane *plane;
  float vectGA[3], vectGB[3];
  int i;
  float det;

  plane = (VisuPlane*)data;
  for (i = 0; i < 3; i++)
    {
      vectGA[i] = ((float*)pointA)[i] - plane->pointG[i];
      vectGB[i] = ((float*)pointB)[i] - plane->pointG[i];
    }
  det = vectGA[0] * vectGB[1] * plane->nVect[2] + vectGB[0] * plane->nVect[1] * vectGA[2] +
    plane->nVect[0] * vectGA[1] * vectGB[2] - vectGA[2] * vectGB[1] * plane->nVect[0] -
    vectGA[1] * vectGB[0] * plane->nVect[2] - vectGA[0] * vectGB[2] * plane->nVect[1];
  if (det < 0.)
    return -1;
  else if (det > 0.)
    return 1;
  else
    return 0;
}
