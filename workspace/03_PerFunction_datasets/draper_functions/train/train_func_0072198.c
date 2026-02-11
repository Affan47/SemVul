fxShift(float shift, Uint8 *target, Uint8 *source, int len) {
  int i, j;


  len /= 4;

  for(i = 0; i < len; i++) {
    for(j = 0; j < 2; j++) {
      Sint32 result = 0;
      int pa;
      float t;

      pa = (int) (i * shift);
      t = (i * shift) - pa;

      result = (Sint32) (
	*( (Sint16*) target + j + 2 * i) * 1.0f +
	*( (Sint16*) source + j + 2 * (pa + 0) ) * (1.0f - t) +
	*( (Sint16*) source + j + 2 * (pa + 1) ) * (t) );

#define MAX_SINT16 ((1 << 15) - 1)
#define MIN_SINT16 (- (1 << 15) )
      if(result > MAX_SINT16) {
	result = MAX_SINT16;
	fprintf(stderr, "overflow\n");
      } else if(result < MIN_SINT16) {
	result = MIN_SINT16;
	fprintf(stderr, "underflow\n");
      }

      *( (Sint16*) target + j + 2 * i ) = (Sint16) result;


    }
  }
  return 4 * fxComputeShiftLen(shift, len);
}
