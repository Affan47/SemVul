vinsideT(CM_t *cm, ESL_DSQ *dsq, int L, Parsetree_t *tr,
	 int r, int z, int i0, int i1, int j1, int j0, int useEL,
	 int allow_begin, int *dmin, int *dmax)
{
  char ***shadow;
  float   sc;
  int     v,y;
  int     j,i;
  int     jp,ip;
  int     yoffset;
  int     b;
  float   bsc;


  if (r == z) {
    InsertTraceNode(tr, tr->n-1, TRACE_LEFT_CHILD, i0, j0, r);
    return 0.;
  }

  if(dmin == NULL && dmax == NULL)
    {
      sc = vinside(cm, dsq, L, r, z, i0, i1, j1, j0, useEL,
		   BE_EFFICIENT,
		   NULL, NULL,
		   NULL, NULL,
		   &shadow,
		   allow_begin,
		   &b, &bsc);
    }
  else
    {
      sc = vinside_b(cm, dsq, L, r, z, i0, i1, j1, j0, useEL,
		     BE_EFFICIENT,
		     NULL, NULL,
		     NULL, NULL,
		     &shadow,
		     allow_begin,
		     &b, &bsc,
		     dmin, dmax);
    }


  v = r;
  j = j0;
  i = i0;


  while (1) {
    jp = j-j1;
    ip = i-i0;


    yoffset = shadow[v][jp][ip];


    switch (cm->sttype[v]) {
    case D_st:            break;
    case MP_st: i++; j--; break;
    case ML_st: i++;      break;
    case MR_st:      j--; break;
    case IL_st: i++;      break;
    case IR_st:      j--; break;
    case S_st:            break;
    default:    cm_Fail("'Inconceivable!'\n'You keep using that word...'");
    }


    if (yoffset == USED_EL)
      {
	InsertTraceNode(tr, tr->n-1, TRACE_LEFT_CHILD, i, j, cm->M);
	break;
      }
    else if (yoffset == USED_LOCAL_BEGIN)
      {
	InsertTraceNode(tr, tr->n-1, TRACE_LEFT_CHILD, i, j, b);
	v = b;
	if (! useEL && v == z) break;
      }
    else
      {


	y = cm->cfirst[v] + yoffset;
	InsertTraceNode(tr, tr->n-1, TRACE_LEFT_CHILD, i, j, y);
	v = y;
	if (! useEL && v == z) break;
      }
  }


  free_vji_shadow_matrix(shadow, cm->M, j1, j0);
  return sc;
}
