push_stack(Transform_config *tc, Transform_directive directive, char *region,
		   Kwv *attrs, int skip, int expand, char *expr)
{
  Transform_stack *stack_el;

  stack_el = ALLOC(Transform_stack);
  stack_el->directive = directive;
  stack_el->region = region;
  stack_el->skipping = skip;
  stack_el->expanding = expand;
  stack_el->expr = expr;
  stack_el->diverted = ds_init(NULL);


  kwv_merge(attrs, tc->global_attrs, KWV_NO_DUPS);
  if (tc->stackp == NULL) {
	stack_el->saved_attrs = NULL;
	stack_el->var_context = var_ns_copy(tc->env->namespaces);
  }
  else {
	Kwv *kwv;

	kwv = var_ns_lookup_kwv(tc->stackp->var_context, "Attr");
	stack_el->saved_attrs = kwv;
	stack_el->var_context = var_ns_copy(tc->stackp->var_context);
	if (kwv != NULL)
	  kwv_merge(attrs, kwv, KWV_NO_DUPS);
  }
  var_ns_replace(&stack_el->var_context, "Attr", attrs);

  stack_el->prev = tc->stackp;
  tc->stackp = stack_el;
  tc->stack_depth++;

  return(stack_el);
}
