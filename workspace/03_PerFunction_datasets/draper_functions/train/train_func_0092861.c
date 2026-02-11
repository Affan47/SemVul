_dxfBuildOrientedManifold(int *nV, float **v, int nT, int *t, int **vlut,
			      int *nE, EdgeS **edges, Htable *e_table, int *fathers)
{

  int
    success = 0;

  int
    nT3    = 3 * nT,
    new_nV = 0;

  float
    *new_v = NULL;

  int
    *new_t     = NULL,
    *old_vlut  = *vlut,
    *new_vlut  = NULL;

  register int i;


  new_t = (int *)   DXAllocateZero (nT3 * sizeof (int));

  if (!new_t) goto error;

  for (new_nV = i = 0; i < nT3; i++)
    {
      int corner_father;


      if ((corner_father = _dxfFather(i,fathers)) == i)
	{
	  new_t[i] = new_nV;
	  new_nV ++;
	}


      else new_t[i] = new_t[corner_father];


    }


  new_vlut = (int *)   DXAllocateZero (new_nV * sizeof (int));

  if (!new_vlut) goto error;


  for (i = 0; i < nT3; i++) if (i == fathers[i])


    new_vlut[new_t[i]] = old_vlut[t[i]];


  if (*vlut)
    {DXFree((Pointer)(*vlut));}

  *vlut = new_vlut;


  new_v    = (float *) DXAllocateZero (new_nV * sizeof (Vertex));

  if (!new_v) goto error;


  for (i = 0; i< nT3; i++)

    if (i == fathers[i])

      memcpy(new_v + 3 * new_t[i], *v + 3 * t[i], sizeof (Vertex));


  if (*v) {DXFree((Pointer)(*v));}


  *v  = new_v;


  *nV = new_nV;


  memcpy(t, new_t, nT3 * sizeof (int));

  DXFree((Pointer) new_t);

  new_t = NULL;


  bzero((char *)e_table, sizeof (Htable));

  if (_dxfIndexEdges(nE, edges, e_table, nT, t))


    success = 1;

  return success;

error:
  if (new_t)    {DXFree((Pointer)new_t);}

  if (new_vlut)
    {
      DXFree((Pointer)new_vlut);


      *vlut = NULL;}

  if (new_v)
    {
      DXFree((Pointer)new_v);


      *v = NULL;
    }

  return 0;
}
