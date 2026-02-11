test_meet_array(void)
{
  printf("\nmeet array %s\n",num_incomplete ? "" : "(* expected)");
  LOOP {
    int i, dim = 6;
    oct_t* o[NB_MEET], *oo;
    ap_abstract0_t* p[NB_MEET], *pp, *ppp;
    for (i=0;i<NB_MEET;i++)
      random_poly_oct(dim, .2, &o[i], &p[i]);
    oo = oct_meet_array(mo,o,NB_MEET); FLAG(mo);
    pp = poly_of_oct(oo);
    ppp = ap_abstract0_meet_array(mp,p,NB_MEET);
    FLAG(mp);
    RESULT(check(oo));
    for (i=0;i<NB_MEET;i++)
      if (oct_is_nleq(mo,oo,o[i])) ERROR("not lower bound");
    if (!ap_abstract0_is_leq(mp,ppp,pp)) ERROR("not poly approx");
    if (ap_abstract0_is_eq(mp,ppp,pp)) RESULT('*');
    if (flag==exact && !ap_abstract0_is_eq(mp,ppp,pp)) ERROR("exact flag");
    for (i=0;i<NB_MEET;i++) { oct_free(mo,o[i]); ap_abstract0_free(mp,p[i]); }
    oct_free(mo,oo); ap_abstract0_free(mp,pp); ap_abstract0_free(mp,ppp);
  } ENDLOOP;
}
