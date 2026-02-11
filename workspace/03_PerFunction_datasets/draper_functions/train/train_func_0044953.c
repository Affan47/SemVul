overbeek_weight(struct term *t, int *ip)
{
  if (Overbeek_world == NULL)
    return 0;
  else {
    int hashval;
    struct term_ptr *p;
    int found = 0;
    struct term *copy = copy_term(t);

    renumber_vars_term(copy);
    hashval = abs(hash_term2(copy) % OVERBEEK_WORLD_SIZE);
    for (p = Overbeek_world[hashval]; p && !found; p = p->next) {
      if (term_ident(copy, p->term->farg->narg->argval)) {
	int rc;
	found = 1;
	rc = str_int(sn_to_str(p->term->farg->argval->sym_num), ip);
      }
    }
    zap_term(copy);
    return found;
  }
}
