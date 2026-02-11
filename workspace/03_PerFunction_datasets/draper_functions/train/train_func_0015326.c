expand_start_loop (int exit_flag)
{
  struct nesting *thisloop = ALLOC_NESTING ();


  thisloop->desc = LOOP_NESTING;
  thisloop->next = loop_stack;
  thisloop->all = nesting_stack;
  thisloop->depth = ++nesting_depth;
  thisloop->data.loop.start_label = gen_label_rtx ();
  thisloop->data.loop.end_label = gen_label_rtx ();
  thisloop->data.loop.continue_label = thisloop->data.loop.start_label;
  thisloop->exit_label = exit_flag ? thisloop->data.loop.end_label : 0;
  loop_stack = thisloop;
  nesting_stack = thisloop;

  do_pending_stack_adjust ();
  emit_queue ();
  emit_note (NOTE_INSN_LOOP_BEG);
  emit_label (thisloop->data.loop.start_label);

  return thisloop;
}
