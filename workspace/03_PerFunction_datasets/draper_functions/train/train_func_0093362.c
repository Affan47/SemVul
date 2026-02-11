delete_moves (void)
{
  struct move_list *ml;
  struct web *s, *t;


  for (ml = wl_moves; ml; ml = ml->next)


    if (ml->move
	&& (s = alias (ml->move->source_web))->reg_rtx
	    == (t = alias (ml->move->target_web))->reg_rtx
	&& s->type != PRECOLORED && t->type != PRECOLORED)
      {
	basic_block bb = BLOCK_FOR_INSN (ml->move->insn);
	df_insn_delete (df, bb, ml->move->insn);
	deleted_move_insns++;
	deleted_move_cost += bb->frequency + 1;
      }
}
