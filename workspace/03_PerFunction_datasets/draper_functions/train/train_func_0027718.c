parse_initial_proof_object(FILE *fp)
{
  struct proof_object *po = get_proof_object();
  Bnode lisp_proof_object = parse_lisp(fp);
  Bnode b;
  Bnode lisp_step;
  if (lisp_proof_object == NULL)
    abend("parse_proof_object: parse_listp returns NULL");
  if (!true_listp(lisp_proof_object))
    abend("parse_proof_object: parse_listp nonlist");

  for (b = lisp_proof_object; !nullp(b); b = b->cdr) {
    struct proof_object_node *pn = connect_new_node(po);
    Bnode e1, e2, e3;
    char *label;
    lisp_step = b->car;
    if (length(lisp_step) < 3)
      abend("parse_proof_object: step length < 3");
    e1 = car(lisp_step);
    e2 = cadr(lisp_step);
    e3 = caddr(lisp_step);
    pn->id = bnode_to_natural(e1);
    if (length(e2) < 1 || !atom(car(e2)))
      abend("parse_proof_object: bad justification (1)");
    label = car(e2)->label;
    if (str_ident(label, "INPUT"))
      pn->rule = P_RULE_INPUT;
    else if (str_ident(label, "EQ-AXIOM"))
      pn->rule = P_RULE_EQ_AXIOM;
    else
      abend("parse_proof_object: bad justification (2)");
    pn->c = bnode_to_clause(e3);
    if (!pn->c)
      abend("parse_proof_object: NULL clause");
  }
  return po;
}
