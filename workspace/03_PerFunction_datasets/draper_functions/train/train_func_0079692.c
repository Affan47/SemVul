clone(GAGenome::CloneMethod flag) const {
  GABin2DecGenome *cpy = new GABin2DecGenome(*ptype);
  if(flag == CONTENTS){ cpy->copy(*this); }
  else{
    cpy->GAGenome::copy(*this);
    cpy->maxX = maxX; cpy->minX = minX;
    *(cpy->ptype) = *ptype;
    cpy->encode = encode;
    cpy->decode = decode;
  }
  return cpy;
}
