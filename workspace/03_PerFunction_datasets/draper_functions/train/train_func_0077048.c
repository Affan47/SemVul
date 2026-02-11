select_edge(equation *cycle, int *need_recalc)
{
  equation *help = NULL;
  equation *solitary = NULL;
  equation *nonharm = NULL;
  BOOL is_harmful_past = FALSE;

  equation *p;

  for(p = cycle; p; p=p->next) {
    if(p->next && p->coefficient.num < 0) {
      equalist *t;
      BOOL pastthis = FALSE;
      BOOL is_found = FALSE;
      BOOL is_harmful = FALSE;
      BOOL is_past = FALSE;
      BOOL is_help = FALSE;
      BOOL is_compensator = FALSE;
      for(t = equats; t; t=t->next) {
	if(t->eq == cycle)
	  pastthis = TRUE;
	else {
	  rational sum = rational_int(0);
	  equation *r, *foundme = NULL;
	  BOOL first_find = TRUE;
	  for(r = t->eq; r; r=r->next) {
	    if(r->next) {
	      int value = *(r->var) ? *(r->var) : *(r->min);
	      sum = rational_add(sum, rational_mult(r->coefficient,
						    rational_int(value)));
	      if(r->count == 1 && r->coefficient.num < 0)
		is_compensator = TRUE;
	      if(r->var == p->var) {
		if(foundme)
		  first_find = FALSE;
		foundme = r;
		is_past = pastthis && (is_past || !is_found);
		is_found = TRUE;
		if(r->coefficient.num > 0)
		  is_harmful = TRUE;
	      }
	    } else if(pastthis && foundme && -sum.num < *(r->min) && first_find
		      && foundme->coefficient.num < 0)
	      is_help = TRUE;
	  }
	}
      }
      if(is_help && !is_harmful && !help)
	help = p;
      if(!is_found) {
	solitary = p;
      } else if(!is_harmful || is_compensator) {
	if(!nonharm || is_past) {
	  is_harmful_past = !is_past;
	  nonharm = p;
	}
      }
    }
  }

  if(help)     return help;
  if(solitary) return solitary;
  if(nonharm)  { if(is_harmful_past) *need_recalc = 2; return nonharm; }

  return NULL;
}
