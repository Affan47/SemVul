CGN_NINT(float a){
  int res=0;

 res = (a) > 0 ? floor(a+0.5) : -floor(a-0.5);
 return res;
}
