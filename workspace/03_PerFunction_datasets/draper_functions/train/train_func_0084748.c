dPlaneSpace (const dVector3 n, dVector3 p, dVector3 q)
{
  dAASSERT (n && p && q);
  if (dFabs(n[2]) > M_SQRT1_2) {

    dReal a = n[1]*n[1] + n[2]*n[2];
    dReal k = dRecipSqrt (a);
    p[0] = 0;
    p[1] = -n[2]*k;
    p[2] = n[1]*k;

    q[0] = a*k;
    q[1] = -n[0]*p[2];
    q[2] = n[0]*p[1];
  }
  else {

    dReal a = n[0]*n[0] + n[1]*n[1];
    dReal k = dRecipSqrt (a);
    p[0] = -n[1]*k;
    p[1] = n[0]*k;
    p[2] = 0;

    q[0] = -n[2]*p[1];
    q[1] = n[2]*p[0];
    q[2] = a*k;
  }
}
