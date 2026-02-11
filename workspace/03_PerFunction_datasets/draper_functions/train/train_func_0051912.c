transposep(const P *pln)
{
     int i;

     for (i = 0; i < pln->rnk - 2; ++i)
	  if (pln->d[i].is != pln->d[i].os)
	       return 0;

     return (pln->d[i].n == pln->d[i+1].n &&
	     pln->d[i].is == pln->d[i+1].os &&
	     pln->d[i].os == pln->d[i+1].is);
}
