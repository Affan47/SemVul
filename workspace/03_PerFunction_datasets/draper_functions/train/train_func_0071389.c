match_literals(struct clause *c1,
			  struct context *s1,
			  int *m1,
			  struct clause *c2,
			  struct context *s2,
			  int *m2,
			  struct trail **trp)
{
  struct literal *l1, *l2;
  int i1, i2, matched, flip;
  struct trail *t_pos;


  for (l2 = c2->first_lit, i2=1; l2 && m2[i2]!=0; l2 = l2->next_lit, i2++);
  if (!l2)
    return(1);
  else {
    matched = 0;
    flip = 0;
    i1 = 1;
    l1 = c1->first_lit;
    while (l1 && !matched) {
      t_pos = *trp;
      if (m1[i1]==0 && l1->sign == l2->sign &&
	  variant(l1->atom, s1, l2->atom, s2, trp, flip)) {
	m1[i1] = (flip ? -i2: i2);
	m2[i2] = (flip ? -i1: i1);
	if (match_literals(c1, s1, m1, c2, s2, m2, trp))
	  matched = 1;
	else {
	  m1[i1] = 0;
	  m2[i2] = 0;
	  clear_subst_2(*trp, t_pos);
	  *trp = t_pos;
	}
      }

      if (check_eq_lit(l1) && check_eq_lit(l2) && !flip) {
	flip = 1;
      }
      else {
	l1 = l1->next_lit;
	i1++;
	flip = 0;
      }
    }
    return(matched);
  }
}
