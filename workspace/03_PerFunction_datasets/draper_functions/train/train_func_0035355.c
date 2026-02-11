b64_decode(char *dest, const char *src) {
  char *seg;
  char *p;
  char *out = dest;
  char v[4];
  int i;


  for(seg = (char*)src; *seg; seg += 4) {

    for(i = 0; i < 4; i++) {
      p = strchr(b64alphabet, seg[i]);
      if(!p) {
        if(seg[i] == '=') v[i] = 0;
        else return -1;
      } else v[i] = p - b64alphabet;
    }


    *(out++) = (v[0] << 2) | (v[1] >> 4);
    if(seg[2] != '=') *(out++) = ((v[1] & 0x0f) << 4) | (v[2] >> 2);
    if(seg[3] != '=') *(out++) = ((v[2] & 0x0f) << 6) | v[3];
  }

  *out = '\0';

  return 0;
}
