SubsampledMatrixSize(const std::vector<unsigned int>&   subsampling,
                                                         std::vector<unsigned int>          isize) const
{
  std::vector<unsigned int>  osize(3,0);
  if (isize.size()) osize = isize;
  else {osize[0] = FieldSz_x(); osize[1] = FieldSz_y(); osize[2] = FieldSz_z();}
  for (unsigned int i=0; i<osize.size(); i++) {
    while (osize[i]%subsampling[i]) osize[i] += 1;
    osize[i] /= subsampling[i];
  }
  return(osize);
}
