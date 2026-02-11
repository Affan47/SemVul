encode_scalar_valueUutf_16le(long value_22X, char * buffer_23X, long count_24X, char *TT0, long *TT1)
{
  long word_26X;
  long word_25X;
 {  if ((65535 < value_22X)) {
    if ((count_24X < 4)) {
      *TT0 = 1;
      *TT1 = 4;
      return 1;}
    else {
      word_25X = 55232 + ((long)(((unsigned long)value_22X)>>10));
      *((unsigned char *) buffer_23X) = (unsigned char) ((255 & word_25X));
      *((unsigned char *) (buffer_23X + 1)) = (unsigned char) (((long)(((unsigned long)word_25X)>>8)));
      word_26X = 56320 + (1023 & value_22X);
      *((unsigned char *) (buffer_23X + 2)) = (unsigned char) ((255 & word_26X));
      *((unsigned char *) (buffer_23X + 3)) = (unsigned char) (((long)(((unsigned long)word_26X)>>8)));
      *TT0 = 0;
      *TT1 = 4;
      return 1;}}
  else {
    if ((count_24X < 2)) {
      *TT0 = 1;
      *TT1 = 2;
      return 1;}
    else {
      *((unsigned char *) buffer_23X) = (unsigned char) ((255 & value_22X));
      *((unsigned char *) (buffer_23X + 1)) = (unsigned char) (((long)(((unsigned long)value_22X)>>8)));
      *TT0 = 0;
      *TT1 = 2;
      return 1;}}}
}
