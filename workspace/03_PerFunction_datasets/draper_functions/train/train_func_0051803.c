_dxfMakeBarycenter(int nV, Vertex *vv, Vertex bary, float *bary_coord)
{
  register int i;
  register u_char j;


  for(j=0;j<3;j++)
    bary[j]=0.0;

  for(i=0;i<nV;i++)
    {
      for(j=0;j<3;j++)
	bary[j]+= bary_coord[i]*vv[i][j];
    }

  return;
}
