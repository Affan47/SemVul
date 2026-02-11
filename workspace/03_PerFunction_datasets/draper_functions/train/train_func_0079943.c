Seqtype(char *seq)
{
  int  saw;
  char c;
  int  po = 0;
  int  nt = 0;
  int  nu = 0;
  int  na = 0;
  int  aa = 0;
  int  no = 0;


  for (saw = 0; *seq != '\0' && saw < 300; seq++)
    {
      c = sre_toupper((int) *seq);
      if (! isgap(c))
	{
	  if (strchr(protonly, c)) po++;
	  else if (strchr(primenuc,c)) {
	    na++;
	    if (c == 'T') nt++;
	    else if (c == 'U') nu++;
	  }
	  else if (strchr(aminos,c)) aa++;
	  else if (isalpha((int) c)) no++;
	  saw++;
	}
    }

  if (no > 0) return kOtherSeq;
  else if (po > 0) return kAmino;
  else if (na > aa) {
    if (nu > nt) return kRNA;
    else return kDNA;
    }
  else return kAmino;
}
