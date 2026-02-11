EscapeQuotes(char *s, char *out, int outSz)

{ char *spt,*spf;
  int i = 0;

memset(out,0,outSz);

 for (spf = s, spt = out; (i < outSz - 2) && (*spf != '\0'); spf++,spt++,i++)
   {
   switch (*spf)
      {
      case '\'':
      case '\"':
          *spt++ = '\\';
          *spt = *spf;
	  i+=3;
          break;

      default:
          *spt = *spf;
	  i++;
          break;
      }
   }

return out;
}
