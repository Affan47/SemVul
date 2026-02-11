copy(const GA3DBinaryStringGenome & orig,
     unsigned int r, unsigned int s, unsigned int t,
     unsigned int x, unsigned int y, unsigned int z,
     unsigned int w, unsigned int h, unsigned int d)
{
  if(w == 0 || x >= orig.nx || r >= nx ||
     h == 0 || y >= orig.ny || s >= ny ||
     d == 0 || z >= orig.nz || t >= nz) return;
  if(x + w > orig.nx) w = orig.nx - x;
  if(y + h > orig.ny) h = orig.ny - y;
  if(z + d > orig.nz) d = orig.nz - z;
  if(r + w > nx) w = nx - r;
  if(s + h > ny) h = ny - s;
  if(t + d > nz) d = nz - t;

  for(unsigned int k=0; k<d; k++)
    for(unsigned int j=0; j<h; j++)
      GABinaryString::copy(orig,
			   (t+k)*ny*nx + (s+j)*nx + r,
			   (z+k)*orig.ny*orig.nx + (y+j)*orig.nx + x, w);
  _evaluated = gaFalse;
}
