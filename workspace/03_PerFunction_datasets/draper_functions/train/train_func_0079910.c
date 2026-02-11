cmdh_select_input_context(struct command* cmd)
{
  int id;
  struct input_context_list** p;

  id = atoi(cmd->arg[0]);
  for (p = &ictx_list; *p; p = &(*p)->next) {
    if ((*p)->id == id) {
      struct input_context_list* sel;
      sel = *p;
      *p = sel->next;
      sel->next = ictx_list;
      ictx_list = sel;
      send_ok();
      return;
    }
  }

  new_input_context(id);
  send_ok();
}
