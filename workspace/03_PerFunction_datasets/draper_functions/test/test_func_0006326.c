F_mpz_sqrtmodptopk(mpz_t res, mpz_t sqrt, mpz_t a, mpz_t p, int k)
{
     mpz_t* tempsqpow = F_mpz_alloc();
     mpz_t* inv = F_mpz_alloc();
     mpz_t* pk = F_mpz_alloc();

     mpz_set(res,sqrt);
     mpz_set(*pk,p);
     for (int i = 2; i<=k; i++)
     {
            mpz_mul(*pk,*pk,p);
            __sqrtmodpow(res,res,a,*pk, *tempsqpow, *inv);
     }

     F_mpz_release();F_mpz_release();F_mpz_release();
}
