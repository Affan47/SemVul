hash_eql(object x) {

  ufixnum h;

  switch (type_of(x)) {

  case t_fixnum:
    h=ufixhash(fix(x));
    break;

  case t_character:
    h = rtb[char_code(x)];
    break;

  case t_bignum:
    {
      MP_INT *mp = MP(x);
      void *v1=mp->_mp_d,*ve=v1+mpz_size(mp);

      h=uarrhash(v1,ve,0,0);
    }
    break;

  case t_ratio:
    h=hash_eql(x->rat.rat_num) + hash_eql(x->rat.rat_den);
    break;

  case t_shortfloat:
    {
      F2ul u;
      u.f=sf(x);
      h=ufixhash(u.ul);
    }
    break;

  case t_longfloat:
    {
      D2ul u;
      u.d=lf(x);
      h=ufixhash(u.ul[0])^ufixhash(u.ul[1]);
    }
    break;

  case t_complex:
    h=hash_eql(x->cmp.cmp_real) + hash_eql(x->cmp.cmp_imag);
    break;

  default:
    h=hash_eq1(x);
    break;

  }

  return MHSH(h);

}
