same_dline(DLine *pA, DLine *pB){
  return pA->h==pB->h && memcmp(pA->z,pB->z,pA->h & LENGTH_MASK)==0;
}
