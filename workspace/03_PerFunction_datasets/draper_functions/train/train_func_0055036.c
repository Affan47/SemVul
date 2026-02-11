_dxfFPlaneForIdenticalVolume(u_short val0, u_short val1, Plane p, Vertex *star_vert,
				      Face *star_face, float star_volume)
{
  static Vertex  n;

  u_short i, val02 = val0 - 2, val013 = val0 + val1 - 3;

  bzero((char *)p, sizeof(Vertex));

  for(i=1; i<=val02; i++)
    {
      u_short v1  = star_face[i][1],
              v2  = star_face[i][2];
      VecProd3(star_vert[v1], star_vert[v2], n);
      AddVec(p, n);
    }

  for(i=val0; i<=val013; i++)
    {
      u_short v1  = star_face[i][1],
              v2  = star_face[i][2];
      VecProd3(star_vert[v1], star_vert[v2], n);
      AddVec(p, n);
    }

  p[3] = -star_volume;


  {
    double norm = NORM3(p);

    if (norm > 0.0)
      for (i=0; i < 4; i++)
	p[i] /= norm;
  }

  return;
}
