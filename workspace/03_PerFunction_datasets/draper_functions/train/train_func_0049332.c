check_final_value (loop, v)
     const struct loop *loop;
     struct induction *v;
{
  struct loop_ivs *ivs = LOOP_IVS (loop);
  struct iv_class *bl;
  rtx final_value = 0;

  bl = REG_IV_CLASS (ivs, REGNO (v->src_reg));


#if 0


  v->replaceable = 0;
#endif

  if ((final_value = final_giv_value (loop, v))
      && (v->always_executed
	  || last_use_this_basic_block (v->dest_reg, v->insn)))
    {
      int biv_increment_seen = 0, before_giv_insn = 0;
      rtx p = v->insn;
      rtx last_giv_use;

      v->replaceable = 1;
      v->not_replaceable = 0;


      last_giv_use = v->insn;

      while (1)
	{
	  p = NEXT_INSN (p);
	  if (p == loop->end)
	    {
	      before_giv_insn = 1;
	      p = NEXT_INSN (loop->start);
	    }
	  if (p == v->insn)
	    break;

	  if (GET_CODE (p) == INSN || GET_CODE (p) == JUMP_INSN
	      || GET_CODE (p) == CALL_INSN)
	    {


	      if (! biv_increment_seen
		  && reg_set_p (v->src_reg, PATTERN (p)))
		biv_increment_seen = 1;

	      if (reg_mentioned_p (v->dest_reg, PATTERN (p)))
		{
		  if (biv_increment_seen || before_giv_insn)
		    {
		      v->replaceable = 0;
		      v->not_replaceable = 1;
		      break;
		    }
		  last_giv_use = p;
		}
	    }
	}


      if (v->replaceable)
	{
	  p = v->insn;
	  while (1)
	    {
	      p = NEXT_INSN (p);
	      if (p == loop->end)
		p = NEXT_INSN (loop->start);
	      if (p == last_giv_use)
		break;

	      if (GET_CODE (p) == JUMP_INSN && JUMP_LABEL (p)
		  && LABEL_NAME (JUMP_LABEL (p))
		  && ((loop_insn_first_p (JUMP_LABEL (p), v->insn)
		       && loop_insn_first_p (loop->start, JUMP_LABEL (p)))
		      || (loop_insn_first_p (last_giv_use, JUMP_LABEL (p))
			  && loop_insn_first_p (JUMP_LABEL (p), loop->end))))
		{
		  v->replaceable = 0;
		  v->not_replaceable = 1;

		  if (loop_dump_stream)
		    fprintf (loop_dump_stream,
			     "Found branch outside giv lifetime.\n");

		  break;
		}
	    }
	}


      if (v->replaceable)
	v->final_value = final_value;
    }

  if (loop_dump_stream && v->replaceable)
    fprintf (loop_dump_stream, "Insn %d: giv reg %d final_value replaceable\n",
	     INSN_UID (v->insn), REGNO (v->dest_reg));
}
