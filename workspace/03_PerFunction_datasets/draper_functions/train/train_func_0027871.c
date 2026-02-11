XConvertCp936extToUtf8(char* buffer_return, int len)
{
  int i = 0, l = 0;
  char *buf;

  if (len < 1) return 0;
  buf = (char*) malloc((unsigned)len);
  memcpy(buf, buffer_return, (unsigned)len);

  if (len == 1) {
	  l += XConvertUcsToUtf8((unsigned int)buf[i], buffer_return + l);
  }
  while (i + 1 < len) {
	  unsigned int ucs;
	  unsigned char b[2];
	  b[0] = (unsigned char) buf[i];
	  b[1] = (unsigned char) buf[i + 1];
	  if (cp936ext_mbtowc(NULL, &ucs, b, 2) == 2) {
		  i += 2;
	  } else {
	      if ( b[0] < 0x80) {
		    ucs = b[0];
		}else{
			      ucs = '?';
		  }
			  i++;
		  }
	  l += XConvertUcsToUtf8(ucs, buffer_return + l);
  }
  if(i + 1 == len) {
      l += XConvertUcsToUtf8((unsigned int)buf[i], buffer_return + l);
  }
  free(buf);
  return l;
}
