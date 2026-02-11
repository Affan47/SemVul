memory() {
  double mem=pow2(header[2]+2)+pow2(header[3])
            +pow2(header[4]+2)+pow2(header[5])
            +header.size();
  int cp=7;
  for (int i=0; i<header[6]; ++i) {
    assert(cp<cend);
    double size=pow2(header[cp+1]);
    switch(header[cp]) {
      case CM: mem+=4*size; break;
      case ICM: mem+=64*size+1024; break;
      case MATCH: mem+=4*size+pow2(header[cp+2]); break;
      case MIX2: mem+=2*size; break;
      case MIX: mem+=4*size*header[cp+3]; break;
      case ISSE: mem+=64*size+2048; break;
      case SSE: mem+=128*size; break;
    }
    cp+=compsize[header[cp]];
  }
  return mem;
}
