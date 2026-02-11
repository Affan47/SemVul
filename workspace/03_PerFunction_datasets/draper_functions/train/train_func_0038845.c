newSol()
{
  int i, j, k;
  double xMin;
  int steps;
  node2_t *Loop[2*MAX_SIG_SIZE1], *CurX, *LeaveX = 0;

#if DEBUG_LEVEL > 3
  printf("EnterX = (%d,%d)\n", _EnterX->i, _EnterX->j);
#endif


  i = _EnterX->i;
  j = _EnterX->j;
  _IsX[i][j] = 1;
  _EnterX->NextC = _RowsX[i];
  _EnterX->NextR = _ColsX[j];
  _EnterX->val = 0;
  _RowsX[i] = _EnterX;
  _ColsX[j] = _EnterX;


  steps = findLoop(Loop);


  xMin = EMDINF;
  for (k=1; k < steps; k+=2)
    {
	if (Loop[k]->val < xMin)
	  {
	    LeaveX = Loop[k];
	    xMin = Loop[k]->val;
	  }
    }


  for (k=0; k < steps; k+=2)
    {
	Loop[k]->val += xMin;
	Loop[k+1]->val -= xMin;
    }

#if DEBUG_LEVEL > 3
  printf("LeaveX = (%d,%d)\n", LeaveX->i, LeaveX->j);
#endif


  i = LeaveX->i;
  j = LeaveX->j;
  _IsX[i][j] = 0;
  if (_RowsX[i] == LeaveX)
    _RowsX[i] = LeaveX->NextC;
  else
    for (CurX=_RowsX[i]; CurX != NULL; CurX = CurX->NextC)
	if (CurX->NextC == LeaveX)
	  {
	    CurX->NextC = CurX->NextC->NextC;
	    break;
	  }
  if (_ColsX[j] == LeaveX)
    _ColsX[j] = LeaveX->NextR;
  else
    for (CurX=_ColsX[j]; CurX != NULL; CurX = CurX->NextR)
	if (CurX->NextR == LeaveX)
	  {
	    CurX->NextR = CurX->NextR->NextR;
	    break;
	  }


  _EnterX = LeaveX;
}
