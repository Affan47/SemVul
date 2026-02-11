matchlf(z,i1,i,op,cl)
char *z, op, cl;
int i, i1;
{ int k;
  if (z[i] != cl)
  { ERROR(("matchlf: wrong end character"));
    return(i);
  }
  k = 0;
  while (1)
  { if (z[i]==op) k--;
    if (z[i]==cl) k++;
    if (k==0) return(i);
    i--;
    if (i<i1)
    { ERROR(("matchlf: unbalanced %c%c: %s",op,cl,z));
      return(i);
    }
  }
}
