subsumes(const flags_t *a, unsigned slvndx_a, const flags_t *b)
{
     if (slvndx_a != INFEASIBLE_SLVNDX) {
	  A(a->timelimit_impatience == 0);
	  return (LEQ(a->u, b->u) && LEQ(b->l, a->l));
     } else {
	  return (LEQ(a->l, b->l)
		  && a->timelimit_impatience <= b->timelimit_impatience);
     }
}
