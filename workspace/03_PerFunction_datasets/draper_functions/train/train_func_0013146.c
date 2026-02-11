is_list_ref_seq(Lex_state *e, Dsvec *ref)
{
  int st;
  Dsvec *dsv;
  Value *value;
  Token ref_type;

  dsv = dsvec_init(NULL, sizeof(Value));
  if ((st = is_list_ref(e, dsv, &ref_type)) != 1)
	return(st);


  if (e->do_eval) {
	value = init_value(NULL, T_LIST, sizeof(Value));
	value->val.listval.list = dsv;
	value->is_alist_reference = (ref_type == T_ALIST);
	dsvec_add_ptr(ref, value);
  }

  while (1) {
	dsv = dsvec_init(NULL, sizeof(Value));
	if ((st = is_list_ref(e, dsv, &ref_type)) != 1)
	  break;
	if (e->do_eval) {
	  value = init_value(NULL, T_LIST, sizeof(Value));
	  value->val.listval.list = dsv;
	  value->is_alist_reference = (ref_type == T_ALIST);
	  dsvec_add_ptr(ref, value);
	}
  }

  if (st == -1)
	return(-1);


  return(1);
}
