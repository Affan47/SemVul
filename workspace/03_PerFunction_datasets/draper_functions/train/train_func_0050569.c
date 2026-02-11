assign_parms_unsplit_complex (struct assign_parm_data_all *all,
			      VEC(tree, heap) *fnargs)
{
  tree parm;
  tree orig_fnargs = all->orig_fnargs;
  unsigned i = 0;

  for (parm = orig_fnargs; parm; parm = TREE_CHAIN (parm), ++i)
    {
      if (TREE_CODE (TREE_TYPE (parm)) == COMPLEX_TYPE
	  && targetm.calls.split_complex_arg (TREE_TYPE (parm)))
	{
	  rtx tmp, real, imag;
	  enum machine_mode inner = GET_MODE_INNER (DECL_MODE (parm));

	  real = DECL_RTL (VEC_index (tree, fnargs, i));
	  imag = DECL_RTL (VEC_index (tree, fnargs, i + 1));
	  if (inner != GET_MODE (real))
	    {
	      real = gen_lowpart_SUBREG (inner, real);
	      imag = gen_lowpart_SUBREG (inner, imag);
	    }

	  if (TREE_ADDRESSABLE (parm))
	    {
	      rtx rmem, imem;
	      HOST_WIDE_INT size = int_size_in_bytes (TREE_TYPE (parm));
	      int align = STACK_SLOT_ALIGNMENT (TREE_TYPE (parm),
						DECL_MODE (parm),
						TYPE_ALIGN (TREE_TYPE (parm)));


	      tmp = assign_stack_local (DECL_MODE (parm), size, align);
	      set_mem_attributes (tmp, parm, 1);
	      rmem = adjust_address_nv (tmp, inner, 0);
	      imem = adjust_address_nv (tmp, inner, GET_MODE_SIZE (inner));
	      push_to_sequence2 (all->first_conversion_insn,
				 all->last_conversion_insn);
	      emit_move_insn (rmem, real);
	      emit_move_insn (imem, imag);
	      all->first_conversion_insn = get_insns ();
	      all->last_conversion_insn = get_last_insn ();
	      end_sequence ();
	    }
	  else
	    tmp = gen_rtx_CONCAT (DECL_MODE (parm), real, imag);
	  SET_DECL_RTL (parm, tmp);

	  real = DECL_INCOMING_RTL (VEC_index (tree, fnargs, i));
	  imag = DECL_INCOMING_RTL (VEC_index (tree, fnargs, i + 1));
	  if (inner != GET_MODE (real))
	    {
	      real = gen_lowpart_SUBREG (inner, real);
	      imag = gen_lowpart_SUBREG (inner, imag);
	    }
	  tmp = gen_rtx_CONCAT (DECL_MODE (parm), real, imag);
	  set_decl_incoming_rtl (parm, tmp, false);
	  i++;
	}
    }
}
