mp_exptmod (mp_int * G, mp_int * X, mp_int * P, mp_int * Y)
{
  int dr;


  if (P->sign == MP_NEG) {
     return MP_VAL;
  }


  if (X->sign == MP_NEG) {
#ifdef BN_MP_INVMOD_C
     mp_int tmpG, tmpX;
     int err;


     if ((err = mp_init(&tmpG)) != MP_OKAY) {
        return err;
     }
     if ((err = mp_invmod(G, P, &tmpG)) != MP_OKAY) {
        mp_clear(&tmpG);
        return err;
     }


     if ((err = mp_init(&tmpX)) != MP_OKAY) {
        mp_clear(&tmpG);
        return err;
     }
     if ((err = mp_abs(X, &tmpX)) != MP_OKAY) {
        mp_clear(&tmpG);
        mp_clear(&tmpX);
        return err;
     }


     err = mp_exptmod(&tmpG, &tmpX, P, Y);
     mp_clear(&tmpG);
     mp_clear(&tmpX);
     return err;
#else

     return MP_VAL;
#endif
  }


#if defined(BN_MP_REDUCE_IS_2K_L_C) && defined(BN_MP_REDUCE_2K_L_C) && \
  defined(BN_S_MP_EXPTMOD_C)
  if (mp_reduce_is_2k_l(P) == MP_YES) {
     return s_mp_exptmod(G, X, P, Y, 1);
  }
#endif

#ifdef BN_MP_DR_IS_MODULUS_C

  dr = mp_dr_is_modulus(P);
#else

  dr = 0;
#endif

#ifdef BN_MP_REDUCE_IS_2K_C

  if (dr == 0) {
     dr = mp_reduce_is_2k(P) << 1;
  }
#endif


#ifdef BN_MP_EXPTMOD_FAST_C
  if (mp_isodd (P) == 1 || dr !=  0) {
    return mp_exptmod_fast (G, X, P, Y, dr);
  } else {
#endif
#ifdef BN_S_MP_EXPTMOD_C

    return s_mp_exptmod (G, X, P, Y, 0);
#else

    return MP_VAL;
#endif
#ifdef BN_MP_EXPTMOD_FAST_C
  }
#endif
}
