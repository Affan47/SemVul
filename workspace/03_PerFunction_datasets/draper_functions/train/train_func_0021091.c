equal(const GA3DBinaryStringGenome& orig,
      unsigned int x, unsigned int y, unsigned int z,
      unsigned int srcx, unsigned int srcy, unsigned int srcz,
      unsigned int w, unsigned int h, unsigned int d) const
{
  unsigned int eq = 0;
  for(unsigned int k=0; k<d; k++)
    for(unsigned int j=0; j<h; j++)
      eq += GABinaryString::equal(orig,
				  (z+k)*ny*nx + (y+j)*nx + x,
				  (srcz+k)*ny*nx + (srcy+j)*nx + srcx,
				  w);
  return eq==d*h ? 1 : 0;
}
