final_biv_value (const struct loop *loop, struct iv_class *bl)
{
  unsigned HOST_WIDE_INT n_iterations = LOOP_INFO (loop)->n_iterations;
  rtx increment, tem;


  if (GET_MODE_CLASS (bl->biv->mode) != MODE_INT)
    return 0;


  if (bl->reversed)
    {
      if (loop_dump_stream)
	fprintf (loop_dump_stream,
		 "Final biv value for %d, reversed biv.\n", bl->regno);

      return const0_rtx;
    }


  if (n_iterations != 0
      && ! loop->exit_count
      && loop_invariant_p (loop, bl->initial_value))
    {
      increment = biv_total_increment (bl);

      if (increment && loop_invariant_p (loop, increment))
	{


	  tem = gen_reg_rtx (bl->biv->mode);
	  record_base_value (REGNO (tem), bl->biv->add_val, 0);
	  loop_iv_add_mult_sink (loop, increment, GEN_INT (n_iterations),
				 bl->initial_value, tem);

	  if (loop_dump_stream)
	    fprintf (loop_dump_stream,
		     "Final biv value for %d, calculated.\n", bl->regno);

	  return tem;
	}
    }


  if (reg_dead_after_loop (loop, bl->biv->src_reg))
    {
      if (loop_dump_stream)
	fprintf (loop_dump_stream,
		 "Final biv value for %d, biv dead after loop exit.\n",
		 bl->regno);

      return const0_rtx;
    }

  return 0;
}
