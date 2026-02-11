resize(int l)
{
  if(l == STA_CAST(int, nx)) return nx;

  if(l == GAGenome::ANY_SIZE)
    l = GARandomInt(minX, maxX);
  else if(l < 0)
    return nx;
  else if(minX == maxX)
    minX=maxX=l;
  else{
    if(l < STA_CAST(int, minX)) l=minX;
    if(l > STA_CAST(int, maxX)) l=maxX;
  }

  GABinaryString::resize(l);
  if(l > STA_CAST(int, nx))
    for(int i=nx; i<l; i++)
      bit(i, GARandomBit());
  nx = l;
  _evaluated = gaFalse;
  return sz;
}
