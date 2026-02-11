val(mpz_t m, int p)
  {
    int ret=0;
    if(p==2)
      {
        int p2Val=mpz_scan1(m,0);


        return p2Val;
      }
    while(mpz_divisible_ui_p(m,p))
      {
        mpz_divexact_ui(m,m,p);
        ret++;
      }

    return ret;
  }
