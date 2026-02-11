get_word(char *dest, char *src, int size, int pos) {

  int k,j;

  k = pos;
  while (src[k] == ' ')  k++;
  if ( (int) (strlen(src) - 1) <= k) return(0);

  j = 0;
  if (src[k] == '{') {
	  while ((src[k] != '}') && (j < size))  {
		  dest[j] = src[k];
		  j++;
		  k++;
	  }
  }
  else while ((src[k] != ' ') && (j < size)) {
    dest[j] = src[k];
    j++;
    k++;
  }
	if (j == size) dest[size - 1] = 0;
	else dest[j] = 0;

  return k;
}
