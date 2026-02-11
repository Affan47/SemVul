dbg_setcxt(I cxl0,C *s){
  I idx=0;C *w=bl(s),d=*w;*w=0;cxl[0]=cxl0;
  for(;*s;*w=d,w=bl(s=cl(w)),d=*w,*w=0)
    if(idx<CXL_SIZE-2)cxl[++idx]=(I)si(strcmp(s,".")?s:"");
    else{
      DH("\343 Bonk!  Hard limit hit: max [+/-]cxt #:%d\n",CXL_SIZE-2);FFL;
      cxl[0]=0;R 1;
    }
  cxl[idx+(idx?1:0)]=0;
R 0;
}
