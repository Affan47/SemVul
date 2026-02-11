lev_editops_find(size_t len1, const lev_byte *string1,
                 size_t len2, const lev_byte *string2,
                 size_t *n)
{
  size_t len1o, len2o;
  size_t i;
  size_t *matrix;


  len1o = 0;
  while (len1 > 0 && len2 > 0 && *string1 == *string2) {
    len1--;
    len2--;
    string1++;
    string2++;
    len1o++;
  }
  len2o = len1o;


  while (len1 > 0 && len2 > 0 && string1[len1-1] == string2[len2-1]) {
    len1--;
    len2--;
  }
  len1++;
  len2++;


  matrix = (size_t*)malloc(len1*len2*sizeof(size_t));
  if (!matrix) {
    *n = (size_t)(-1);
    return NULL;
  }
  for (i = 0; i < len2; i++)
    matrix[i] = i;
  for (i = 1; i < len1; i++)
    matrix[len2*i] = i;


  for (i = 1; i < len1; i++) {
    size_t *prev = matrix + (i - 1)*len2;
    size_t *p = matrix + i*len2;
    size_t *end = p + len2 - 1;
    const lev_byte char1 = string1[i - 1];
    const lev_byte *char2p = string2;
    size_t x = i;
    p++;
    while (p <= end) {
      size_t c3 = *(prev++) + (char1 != *(char2p++));
      x++;
      if (x > c3)
        x = c3;
      c3 = *prev + 1;
      if (x > c3)
        x = c3;
      *(p++) = x;
    }
  }


  return editops_from_cost_matrix(len1, string1, len1o,
                                  len2, string2, len2o,
                                  matrix, n);
}
