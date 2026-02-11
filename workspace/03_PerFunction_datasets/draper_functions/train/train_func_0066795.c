angle_eng(int atype, int i, int j, int k)
{


  if (i == -1 || k == -1) return 0.0;
  return force->angle->single(atype,i,j,k);
}
