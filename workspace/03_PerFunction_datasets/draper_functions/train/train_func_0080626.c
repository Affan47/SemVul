cfg_layout_can_merge_blocks_p (basic_block a, basic_block b)
{

  return (a->succ && !a->succ->succ_next && a->succ->dest == b
	  && !b->pred->pred_next && a != b

	  && !(a->succ->flags & EDGE_COMPLEX)
	  && a != ENTRY_BLOCK_PTR && b != EXIT_BLOCK_PTR


	  && (GET_CODE (BB_END (a)) != JUMP_INSN
	      || (reload_completed
		  ? simplejump_p (BB_END (a)) : onlyjump_p (BB_END (a)))));
}
