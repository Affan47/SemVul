decode_scalar_valueUutf_16le(char * buffer_35X, long count_36X, char *TT0, long *TT1, long *TT2)
{
  long word1_38X;
  long word0_37X;
 {  if ((count_36X < 2)) {
    *TT0 = 1;
    *TT1 = 0;
    *TT2 = 2;
    return 1;}
  else {
    word0_37X = (*((unsigned char *) buffer_35X)) + ((((*((unsigned char *) (buffer_35X + 1))))<<8));
    if ((word0_37X < 55296)) {
      *TT0 = 0;
      *TT1 = word0_37X;
      *TT2 = 2;
      return 1;}
    else {
      if ((57343 < word0_37X)) {
        *TT0 = 0;
        *TT1 = word0_37X;
        *TT2 = 2;
        return 1;}
      else {
        if ((count_36X < 4)) {
          *TT0 = 1;
          *TT1 = 0;
          *TT2 = 4;
          return 1;}
        else {
          if ((56319 < word0_37X)) {
            *TT0 = 0;
            *TT1 = 0;
            *TT2 = 0;
            return 0;}
          else {
            word1_38X = (*((unsigned char *) (buffer_35X + 2))) + ((((*((unsigned char *) (buffer_35X + 3))))<<8));
            if ((word1_38X < 56320)) {
              *TT0 = 0;
              *TT1 = 0;
              *TT2 = 0;
              return 0;}
            else {
              if ((57343 < word1_38X)) {
                *TT0 = 0;
                *TT1 = 0;
                *TT2 = 0;
                return 0;}
              else {
                *TT0 = 0;
                *TT1 = ((-56557568 + (((word0_37X)<<10))) + (1023 & word1_38X));
                *TT2 = 4;
                return 1;}}}}}}}}
}
