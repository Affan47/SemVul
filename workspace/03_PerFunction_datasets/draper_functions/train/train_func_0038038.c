cfg_layout_redirect_edge (e, dest)
     edge e;
     basic_block dest;
{
  basic_block src = e->src;
  basic_block old_next_bb = src->next_bb;


  src->next_bb = NULL;
  if (e->flags & EDGE_FALLTHRU)
    {

      if (GET_CODE (src->end) == JUMP_INSN
	  && JUMP_LABEL (src->end) == e->dest->head)
	{
          if (!redirect_jump (src->end, block_label (dest), 0))
	    abort ();
	}


      if (src->succ->succ_next
	  && !src->succ->succ_next->succ_next)
	{
	  edge s = e->succ_next ? e->succ_next : src->succ;
	  if (s->dest == dest
	      && any_condjump_p (src->end)
	      && onlyjump_p (src->end))
	    delete_insn (src->end);
	}
      redirect_edge_succ_nodup (e, dest);
    }
  else
    redirect_edge_and_branch (e, dest);


  if (simplejump_p (src->end))
    {
      delete_insn (src->end);
      delete_barrier (NEXT_INSN (src->end));
      src->succ->flags |= EDGE_FALLTHRU;
    }
  src->next_bb = old_next_bb;
}
