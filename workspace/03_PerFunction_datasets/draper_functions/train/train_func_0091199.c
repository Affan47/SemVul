outfilter_ascii_ps(const char *buf,int len,void *context)
{
  struct OUTFILTER_PS *of=context;
  OUTPUT_FN out=of->out;
  int iA;

  (*out)("<",1,of->ctx);
  of->len++;

  const char *last=buf;
  char tmp[256];
  while (len>0) {
    for (iA=0;(iA<76)&&(len>0);iA+=2,len--) {
      const unsigned char ch=buf[iA>>1];
      tmp[iA]="0123456789abcdef"[ch>>4];
      tmp[iA+1]="0123456789abcdef"[ch&0x0f];
    }
    buf+=iA>>1;
    if (buf<last+64000) {
      if (len>0) {
        tmp[iA++]='\n';
      }
      (*out)(tmp,iA,of->ctx);
    } else {
      last=buf;
      strcpy(tmp+iA,"00>\n<");
      iA+=5;
      (*out)(tmp,iA,of->ctx);
    }
    of->len+=iA;
  }

  (*out)("00>\n",4,of->ctx);
  of->len+=4;
}
