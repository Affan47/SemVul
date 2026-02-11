bs_FcmpCT( s1, s2) F *s1, *s2;
{
  REG int count=Itemcount;
  REG int result=0;
  REG F a, b;

  while(count-- && !result) {
    a=*s1++; b=*s2++;
    if (isnegative(b) != (result = isnegative(a))) {
      result = (result)?-1:1;
      break;
    }
    if (result) { a=-a; b=-b; }
    if (a<b) result = ((b<=CT*a)?0:((result)?1:-1));
    else result = ((a<=CT*b)?0:((result)?-1:1));
  }
  return(result);
}
