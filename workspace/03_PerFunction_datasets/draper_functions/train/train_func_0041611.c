test_polyhedra_conversion(void)
{
  printf("\nconversion to polyhedra %s\n",num_incomplete ? "" : "(* expected)");
  LOOP {
    oct_t *o, *o2;
    ap_abstract0_t *p, *p2;
    o = random_oct(2,.1);
    p = poly_of_oct(o);
    o2 = oct_of_poly(p);
    p2 = poly_of_oct(o2);
    RESULT(check(o)); check(o2);
    if (oct_is_nleq(mo,o,o2)) {
      ERROR("oct not included in");
      print_oct("o",o);
      print_poly("p",p);
      print_oct("o2",o2);
    }
    if (!ap_abstract0_is_leq(mp,p,p2)) {
      ERROR("poly not included in");
      print_oct("o",o);
      print_poly("p",p);
      print_oct("o2",o2);
      print_poly("p2",p2);
    }
    if (oct_is_eq(mo,o,o2) && ap_abstract0_is_eq(mp,p,p2)) RESULT('*');
    if (flag>=best && (oct_is_neq(mo,o,o2) || !ap_abstract0_is_eq(mp,p,p2))) ERROR("best flag");
    oct_free(mo,o); oct_free(mo,o2); ap_abstract0_free(mp,p); ap_abstract0_free(mp,p2);
  } ENDLOOP;
  {
    oct_t *o;
    ap_abstract0_t *p;
    bool r;
    flag = exact;
    o = oct_bottom(mo,0,7);
    p = poly_of_oct(o);
    r = ap_abstract0_is_bottom(mp,p); FLAG(mp);
    if (flag>=best && !r) printf("poly_is_bottom failed\n");
    oct_free(mo,o); ap_abstract0_free(mp,p);
  }
  {
    oct_t *o;
    ap_abstract0_t *p;
    o = oct_top(mo,0,7);
    p = poly_of_oct(o);
    if (!ap_abstract0_is_top(mp,p) && mp->result.flag_exact) printf("poly_is_top failed\n");
    oct_free(mo,o); ap_abstract0_free(mp,p);
  }
}
