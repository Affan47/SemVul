ginteg_t (int k, creal* f, creal* g)
{
  creal tmp = 0.F;
  int i, next[3]={1,2,0};

  if (__quadra)
    {
      if(g)
      		for (i = 0;i < 3;i++)
        		tmp += (f[3*k+i]+f[3*k+next[i]])*(g[3*k+i]+g[3*k+next[i]])/2.F;
        else
        	for (i = 0;i < 3;i++)
        		tmp += (f[3*k+i]+f[3*k+next[i]]);
      return tmp*area[k]/6.F;
    }
  else
    {
      if(g)
      	for (i = 0;i < 3;i++)
        	tmp += (f[me[k][i]] + f[me[k][next[i]]])*(g[me[k][i]] + g[me[k][next[i]]])/2.F;
        else
      	for (i = 0;i < 3;i++)
        	tmp += (f[me[k][i]] + f[me[k][next[i]]]);
      return tmp*area[k]/6.F;
    }
}
