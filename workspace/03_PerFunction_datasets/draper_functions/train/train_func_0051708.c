BuildEdgeStarVal1Is3(Vertex *vert, Face *face,
				  int v0, int v1, int val0, int val01,
				  int val02, int *vstar0, Vertex *surfvert)
{
  register int i,i1;


  for (i=0, i1=1; i< val01; i++, i1++)
    memcpy(vert[i], surfvert[vstar0[i1]], sizeof(Vertex));
  memcpy(vert[val01], surfvert[v0], sizeof(Vertex));


  memcpy(vert[val0], surfvert[v1], sizeof(Vertex));


 face[0][0] = val01; face[0][1] = val0; face[0][2] = 0;

  for (i = 1, i1 = 0; i <= val02; i++, i1++)
    {
      face[i][0] =  val01; face[i][1] =  i1; face[i][2] =  i;
    }
  face[val01][0] = val01;
  face[val01][1] = val02;
  face[val01][2] = val0;

  face[val0][0] = val0;
  face[val0][1] = val02;
  face[val0][2] = 0;

  return;
}
