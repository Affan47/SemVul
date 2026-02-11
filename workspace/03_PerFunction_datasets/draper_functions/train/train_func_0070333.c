ikrt_fxrandom(ikptr x){
  long int mask = 1;
  long int n = unfix(x);
  {
    while(mask < n){
      mask = (mask << 1) | 1;
    }
  }
  while(1){
    long r = rand() & mask;
    if(r < n){
      return fix(r);
    }
  }
}
