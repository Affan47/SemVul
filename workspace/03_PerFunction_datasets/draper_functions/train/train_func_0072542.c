generate(real *radposn, real *radwght)
{
  radposn[0] = rl;
  radwght[0]  = (rl+grdc)*rl*rl*h;
  for(int ip=1; ip<gridSize; ip++) {
    radposn[ip] = (radposn[ip-1]+grdc)*eph-grdc;
    radwght[ip] = (radposn[ip]  +grdc)*radposn[ip]*radposn[ip]*h;
  }
}
