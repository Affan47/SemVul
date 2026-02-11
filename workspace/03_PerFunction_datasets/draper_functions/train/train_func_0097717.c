rcr_transdecode(GtUchar ref, GtBitsequence transcode,
                               GtAlphabet *alpha)
{
  GtUchar code_a = gt_alphabet_encode(alpha, 'A'),
          code_c = gt_alphabet_encode(alpha, 'C'),
          code_g = gt_alphabet_encode(alpha, 'G'),
          code_t = gt_alphabet_encode(alpha, 'T');

  if (ref == (GtUchar) WILDCARD) {
    switch (transcode) {
       case 0:
         return code_a;
       case 1:
         return code_c;
       case 2:
         return code_g;
       case 3:
         return code_t;
    }
  }
  else if (transcode == (GtBitsequence) 3)
    return (GtUchar) WILDCARD;
  else {
    if (ref == code_a) {
      switch (transcode) {
        case 0:
          return code_c;
        case 1:
          return code_g;
        case 2:
          return code_t;
      }
    }
    if (ref == code_c) {
       switch (transcode) {
         case 0:
           return code_a;
         case 1:
           return code_g;
         case 2:
           return code_t;
         }
    }
    if (ref == code_g) {
      switch (transcode) {
        case 0:
          return code_a;
        case 1:
          return code_c;
        case 2:
          return code_t;
      }
    }
    if (ref == code_t) {
      switch (transcode) {
        case 0:
          return code_a;
        case 1:
          return code_c;
        case 2:
          return code_g;
      }
    }
  }
  return (GtUchar) GT_UNDEF_UCHAR;
}
