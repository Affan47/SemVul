restoreundo(void)
{
  strid_t stack;
  int i;
  glui32 wid, hei;
  move_difference *p = movelist;

  if(!p || move_index < 0)
    return FALSE;

  for(i = 0; i < move_index; i++) {
    p=p->next;
    if(!p)
      return FALSE;
  }
  move_index++;

  n_memcpy(z_memory, prevstate, dynamic_size);

  quetzal_undiff(prevstate, dynamic_size, p->delta, p->deltalength, TRUE);

  stack = glk_stream_open_memory((char *) p->stackchunk, p->stacklength,
				 filemode_Read, 0);

  quetzal_stack_restore(stack, p->stacklength);
  glk_stream_close(stack, NULL);

  if(p->PC_in_instruction) {
    PC = p->PC;
    mop_store_result(2);
    false_undo = FALSE;
  } else {
    PC = p->oldPC;
    false_undo = TRUE;
  }
  has_done_save_undo = TRUE;

  z_find_size(&wid, &hei);
  set_header(wid, hei);
  return TRUE;
}
