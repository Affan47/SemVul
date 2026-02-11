mat44_to_newmat(mat44 inmat)
{
  Matrix retmat(4,4);
  for (int ii=0; ii<4; ii++) {
    for (int jj=0; jj<4; jj++) {
      retmat(ii+1,jj+1) = inmat.m[ii][jj];
    }
  }
  return retmat;
}
