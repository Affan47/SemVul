resort(pv,xev,dig)
double *xev;
INT *pv, *dig;
{ double d0, d1, d2;
  INT i;
  d0 = d1 = d2 = 0;
  for (i=0; i<3; i++)
  { d0 += (xev[3*pv[11]+i]-xev[3*pv[1]+i])*(xev[3*pv[11]+i]-xev[3*pv[1]+i]);
    d1 += (xev[3*pv[ 7]+i]-xev[3*pv[2]+i])*(xev[3*pv[ 7]+i]-xev[3*pv[2]+i]);
    d2 += (xev[3*pv[ 6]+i]-xev[3*pv[3]+i])*(xev[3*pv[ 6]+i]-xev[3*pv[3]+i]);
  }
  if ((d0<=d1) & (d0<=d2))
  { dig[0] = pv[1]; dig[1] = pv[11];
    dig[2] = pv[2]; dig[3] = pv[7];
    dig[4] = pv[3]; dig[5] = pv[6];
  }
  else if (d1<=d2)
  { dig[0] = pv[2]; dig[1] = pv[7];
    dig[2] = pv[1]; dig[3] = pv[11];
    dig[4] = pv[3]; dig[5] = pv[6];
  }
  else
  { dig[0] = pv[3]; dig[1] = pv[6];
    dig[2] = pv[2]; dig[3] = pv[7];
    dig[4] = pv[1]; dig[5] = pv[11];
  }
}
