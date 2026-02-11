decide_peel_once_rolling (struct loop *loop, int flags ATTRIBUTE_UNUSED)
{
  struct niter_desc *desc;

  if (dump_file)
    fprintf (dump_file, "\n;; Considering peeling once rolling loop\n");


  if ((unsigned) PARAM_VALUE (PARAM_MAX_ONCE_PEELED_INSNS) < loop->ninsns)
    {
      if (dump_file)
	fprintf (dump_file, ";; Not considering loop, is too big\n");
      return;
    }


  desc = get_simple_loop_desc (loop);


  if (!desc->simple_p
      || desc->assumptions
      || desc->infinite
      || !desc->const_iter
      || (desc->niter != 0
	  && max_loop_iterations_int (loop) != 0))
    {
      if (dump_file)
	fprintf (dump_file,
		 ";; Unable to prove that the loop rolls exactly once\n");
      return;
    }


  loop->lpt_decision.decision = LPT_PEEL_COMPLETELY;
}
