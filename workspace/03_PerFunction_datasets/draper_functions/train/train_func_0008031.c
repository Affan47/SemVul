geometry_rule_unif(struct clause *giv_cl)
{
  if (giv_cl->first_lit && !giv_cl->first_lit->next_lit &&
      pos_eq_lit(giv_cl->first_lit)) {

    struct term *a, *b;
    int pos_vec[MAX_DEPTH];

    a = giv_cl->first_lit->atom->farg->argval;
    b = giv_cl->first_lit->atom->farg->narg->argval;

    geo_recurse_unif(a, b, giv_cl, pos_vec, 0);
  }

}
