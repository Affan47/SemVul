getDigits(const char *zDate, ...){
  va_list ap;
  int val;
  int N;
  int min;
  int max;
  int nextC;
  int *pVal;
  int cnt = 0;
  va_start(ap, zDate);
  do{
    N = va_arg(ap, int);
    min = va_arg(ap, int);
    max = va_arg(ap, int);
    nextC = va_arg(ap, int);
    pVal = va_arg(ap, int*);
    val = 0;
    while( N-- ){
      if( !isdigit(*(u8*)zDate) ){
        goto end_getDigits;
      }
      val = val*10 + *zDate - '0';
      zDate++;
    }
    if( val<min || val>max || (nextC!=0 && nextC!=*zDate) ){
      goto end_getDigits;
    }
    *pVal = val;
    zDate++;
    cnt++;
  }while( nextC );
end_getDigits:
  va_end(ap);
  return cnt;
}
