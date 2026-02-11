add(double *m, int *n, int c, double *b)
{
  int i=0;


       if(m[*n *c+c] == 0)
       {
          if(fabs(m[*n *(c+1)+c]) != 0)
          {
 	    for(i=0; i<*n;i++)
	    {
	      m[*n *c+i]+=m[*n *(c+1)+i];
            }
	      b[c]+=b[c+1];
          }
       }
return;
}
