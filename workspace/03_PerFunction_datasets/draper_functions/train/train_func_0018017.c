ExpandBands(CM_t *cm, int tlen, int *dmin, int *dmax)
{
  int v;
  int diff;
  int root_min;
  int root_max;
  int M = cm->M;
  root_min = dmin[0];
  root_max = dmax[0];

  if(tlen < root_min)
    {
      diff = root_min - tlen;
      for(v=0; v<M; v++)
	{
	  dmin[v] -= diff;
	  if((cm->sttype[v] == MP_st) && (dmin[v] < 2))
	    dmin[v] = 2;
	  else if(((cm->sttype[v] == IL_st) || (cm->sttype[v] == ML_st))
		  && (dmin[v] < 1))
	    dmin[v] = 1;
	  else if(((cm->sttype[v] == IR_st) || (cm->sttype[v] == MR_st))
		  && (dmin[v] < 1))
	    dmin[v] = 1;
	  else if(dmin[v] < 0)
	    dmin[v] = 0;
	}
    }
  else if(tlen > root_max)
    {
      diff = tlen - root_min;
      for(v=0; v<M; v++)
	{
	  dmax[v] += diff;
	}
    }
}
