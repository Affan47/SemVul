pop_frame_list (struct list_head *undo_list, struct list_head *redo_list)
{
  rp_screen *screen = current_screen();
  rp_frame_undo *first, *new;


  list_first (first, undo_list, node);
  if (!first)
    return NULL;


  new = xmalloc (sizeof(rp_frame_undo));
  new->frames = fdump (screen);
  new->screen = screen;
  list_add (&new->node, redo_list);

  list_del (&(first->node));
  return first;
}
