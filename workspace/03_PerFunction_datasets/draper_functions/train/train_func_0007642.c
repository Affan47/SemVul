projection (float *f)
{
  int             i;
  femPoint         *rp = __t->rp;

  proj = new femPoint[__t->getNumberOfPoints()];
  for (i = 0; i < __t->getNumberOfPoints(); i++)
     {
       proj[i][0] = rp[i][0] / 5;
       proj[i][1] = f[i] + rp[i][1] / 3;
     }
}
