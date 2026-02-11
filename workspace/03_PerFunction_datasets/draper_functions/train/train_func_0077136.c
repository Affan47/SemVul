CentroidEdgeLink(Vertex centroid, Vertex *vert, int val0, int val02, int val014)
{
  register int i;
  register u_char j;

  bzero((char *)centroid, sizeof(Vertex));

  for(j=0;j<3;j++)
    {
      for(i=0; i<=val02; i++)

	centroid[j] += vert[i][j];

      for(i=val0; i<=val014; i++)

	centroid[j] += vert[i][j];

      centroid[j] /= val014;
    }

  return;
}
