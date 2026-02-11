init_giv_select(Plist rules)
{
  Plist p;

  for (p = rules; p; p = p->next) {
    Term t = p->v;
    int n = 0;
    Term order_term;
    Term property_term;
    Giv_select gs;
    if (!is_term(t, "=", 2) ||
	!is_term(ARG(t,0), "part", 4) ||
	!CONSTANT(ARG(ARG(t,0),0)) ||
	!(is_constant(ARG(ARG(t,0),1), "high") ||
	  is_constant(ARG(ARG(t,0),1), "low")) ||
	!((n = natural_constant_term(ARG(t,1))) > 0))
      fatal_error("Given selection rule must be: "
		  "part(<name>,high|low,age|wt|random,<property>)=<n>");

    order_term = ARG(ARG(t,0),2);
    property_term = ARG(ARG(t,0),3);
    gs = get_giv_select();

    if (is_constant(ARG(ARG(t,0),1), "high")) {
      High.selectors = plist_append(High.selectors, gs);
      High.cycle_size += n;
    }
    else {
      Low.selectors  = plist_append(Low.selectors,  gs);
      Low.cycle_size += n;
    }

    gs->name = term_symbol(ARG(ARG(t,0),0));
    gs->part = n;
    if (is_constant(order_term,"weight")) {
      gs->order = GS_ORDER_WEIGHT;
      gs->compare = (Ordertype (*) (void *, void *)) cl_wt_id_compare;
    }
    else if (is_constant(order_term,"age")) {
      gs->order = GS_ORDER_AGE;
      gs->compare = (Ordertype (*) (void *, void *)) cl_id_compare;
    }
    else if (is_constant(order_term,"random")) {
      gs->order = GS_ORDER_RANDOM;
      gs->compare = (Ordertype (*) (void *, void *)) cl_id_compare;
    }
    else
      fatal_error("Given selection order must be weight, age, or random.");
    gs->property = compile_clause_eval_rule(property_term);
    if (gs->property == NULL)
      fatal_error("Error in clause-property expression of given selection rule");
    else if (rule_contains_semantics(gs->property))
      Rule_needs_semantics = TRUE;
  }
  High.current = High.selectors;
  Low.current = Low.selectors;
}
