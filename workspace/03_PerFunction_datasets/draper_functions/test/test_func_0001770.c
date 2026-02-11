sqrt(const gfield &x)
    {
        if(!x.len) { len = 0; return true; }
#if GF_BITS==224
#error Unsupported GF
#else
        ASSERT((P.digits[0]%4)==3);
        static const gfint Padd1div4(gfint(P).add(bigint<1>(1)).rshift(2));
        switch(legendre(x))
        {
            case 0: len = 0; return true;
            case -1: return false;
            default: pow(x, Padd1div4); return true;
        }
#endif
    }
