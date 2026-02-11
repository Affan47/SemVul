_dxfParentVertexStar(int vf, int t0, u_short val, int *star, SimpData *simp_data)


{
  int *estar = star  + val;
  int *vstar = estar + val;
  register int i;
  int t = t0;


  for(i=1;i<val;i++)
    {
      register u_char j=0;
      int vA,vAf,vB,vBf,ef, e_num, *endpoints, *facing_tris;
      EdgeS *edg, *edgf;

      t = FATHER(t, simp_data->triangle_father);


      star[i] = t;
      do
	{
	  vA = simp_data->triangles[3 * t + j];
	  vB = simp_data->triangles[3 * t + (j+2)%3];
	  vAf  = FATHER(vA, simp_data->vertex_father);
	}
      while((j++ < 3) && (vAf != vf));


      edg   = _dxfFindEdge(simp_data->e_table,vA,vB);

      e_num = (int) (edg - simp_data->edge_array);


      ef    = FATHER (e_num, simp_data->edge_father);

      estar[i] = ef;


      edgf = simp_data->edge_array+ef;

      endpoints   = SurfEdgeGetVertices(edgf);
      facing_tris = SurfEdgeGetTriangles(edgf);

      vAf  = FATHER(endpoints[0], simp_data->vertex_father);
      vBf  = FATHER(endpoints[1], simp_data->vertex_father);


      if (vAf == vf)
	{
	  vstar[i] = vBf;


	  t        = facing_tris[0];
	}
      else
	{
	  vstar[i] = vAf;
	  t        = facing_tris[1];
	 }

    }

  return;
}
