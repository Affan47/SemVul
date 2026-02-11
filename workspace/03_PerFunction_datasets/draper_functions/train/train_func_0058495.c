fmt_xlong(char* s,unsigned int i) {
  char* bak=s;
  *s=tohex((i>>12)&0xf); if (s!=bak || *s!='0') ++s;
  *s=tohex((i>>8)&0xf); if (s!=bak || *s!='0') ++s;
  *s=tohex((i>>4)&0xf); if (s!=bak || *s!='0') ++s;
  *s=tohex(i&0xf);
  return s-bak+1;
}
