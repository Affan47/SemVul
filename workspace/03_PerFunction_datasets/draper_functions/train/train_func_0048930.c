equal(const GAGenome & c) const
{
  if(this == &c) return 1;
  const GA3DBinaryStringGenome& b = DYN_CAST(const GA3DBinaryStringGenome&, c);
  if(nx != b.nx || ny != b.ny || nz != b.nz) return 0;
  int val=0;
  for(unsigned int k=0; k<nz && val==0; k++)
    for(unsigned int j=0; j<ny && val==0; j++)
      val = GABinaryString::equal(b,k*ny*nx,k*ny*nx,nx) ? 0 : 1;
  return(val ? 0 : 1);
}
