propagate_typeinfo(void)
{
  tuple *tp;


  for (tp = tuples; tp->type; tp++)
  {
    if (tp->type == GETS || tp->type == RESIZE
	|| tp->type == WRITE_IN || tp->type == READ_OUT
	|| tp->type == FROM || tp->type == MANYFROM
	|| tp->type == FORGET || tp->type == RESUME
	|| tp->type == COMPUCOME || tp->type == UNKNOWN)
      typecast(tp->type == MANYFROM ? tp->u.node->lval : tp->u.node);
    if (tp->type == WRITE_IN) coopt = false;

  }
}
