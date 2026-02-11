expand_goto (label)
     tree label;
{
  tree context;


  context = decl_function_context (label);
  if (context != 0 && context != current_function_decl)
    {
      struct function *p = find_function_data (context);
      rtx label_ref = gen_rtx_LABEL_REF (Pmode, label_rtx (label));
      rtx handler_slot, static_chain, save_area, insn;
      tree link;


      handler_slot = p->x_nonlocal_goto_handler_slots;
      for (link = p->x_nonlocal_labels; TREE_VALUE (link) != label;
	   link = TREE_CHAIN (link))
	handler_slot = XEXP (handler_slot, 1);
      handler_slot = XEXP (handler_slot, 0);

      p->has_nonlocal_label = 1;
      current_function_has_nonlocal_goto = 1;
      LABEL_REF_NONLOCAL_P (label_ref) = 1;


      static_chain = copy_to_reg (lookup_static_chain (label));


      handler_slot = copy_to_reg (replace_rtx (copy_rtx (handler_slot),
					       virtual_stack_vars_rtx,
					       static_chain));


      save_area = p->x_nonlocal_goto_stack_level;
      if (save_area)
	save_area = replace_rtx (copy_rtx (save_area),
				 virtual_stack_vars_rtx, static_chain);

#if HAVE_nonlocal_goto
      if (HAVE_nonlocal_goto)
	emit_insn (gen_nonlocal_goto (static_chain, handler_slot,
				      save_area, label_ref));
      else
#endif
	{


	  emit_move_insn (hard_frame_pointer_rtx, static_chain);
	  emit_stack_restore (SAVE_NONLOCAL, save_area, NULL_RTX);


	  emit_insn (gen_rtx_USE (VOIDmode, hard_frame_pointer_rtx));
	  emit_insn (gen_rtx_USE (VOIDmode, stack_pointer_rtx));
	  emit_indirect_jump (handler_slot);
	}


      for (insn = get_last_insn (); insn; insn = PREV_INSN (insn))
	{
	  if (GET_CODE (insn) == JUMP_INSN)
	    {
	      REG_NOTES (insn) = alloc_EXPR_LIST (REG_NON_LOCAL_GOTO,
						  const0_rtx, REG_NOTES (insn));
	      break;
	    }
	  else if (GET_CODE (insn) == CALL_INSN)
	      break;
	}
    }
  else
    expand_goto_internal (label, label_rtx (label), NULL_RTX);
}
