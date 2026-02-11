putSubstr1(int *SA, int *s, int n) {
  int h, i, j;

  for(i=0; i<n; i++) SA[i]=EMPTY;

  int c, c1, t, t1;
  c1=s[n-2];
  t1=0;
  for(i=n-2; i>0; i--) {
    c=c1; t=t1;
    c1=s[i-1];
    t1=c1<c || (c1==c && t);
    if(t && !t1) {
      if(SA[c]>=0) {


        int foo, bar;
        foo=SA[c];
        for(h=c+1; SA[h]>=0; h++)
        { bar=SA[h]; SA[h]=foo; foo=bar; }
        SA[h]=foo;

        SA[c]=EMPTY;
      }

      int d=SA[c];
      if(d==EMPTY) {
        if(SA[c-1]==EMPTY) {
          SA[c]=-1;
          SA[c-1]=i;
        }
        else
          SA[c]=i;
      }
      else {
          int pos=c+d-1;
          if(SA[pos]!=EMPTY) {


            for(h=0; h<-d; h++)
              SA[c-h]=SA[c-h-1];
            pos++;
          }
          else
            SA[c]--;

          SA[pos]=i;
      }
    }
  }


  for(i=n-1; i>0; i--) {
    j=SA[i];
    if(j<0 && j!=EMPTY) {
      for(h=0; h<-j; h++)
        SA[i-h]=SA[i-h-1];
      SA[i-h]=EMPTY;
    }
  }


  SA[0]=n-1;
}
