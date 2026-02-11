complete_pending_execs(struct predicate *p)
{
  if (NULL == p)
    return;

  complete_pending_execs(p->pred_left);


  if (pred_is(p, pred_exec) && p->args.exec_vec.multiple)
    {
      struct exec_val *execp = &p->args.exec_vec;


      if (execp->state.todo)
	{

	  launch (&execp->ctl, &execp->state);
	}
    }

  complete_pending_execs(p->pred_right);
}
