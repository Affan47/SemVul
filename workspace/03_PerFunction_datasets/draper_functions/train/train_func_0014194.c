var_completions (char *str UNUSED)
{
  struct list_head *list;
  struct set_var *cur;


  list = xmalloc (sizeof (struct list_head));
  INIT_LIST_HEAD (list);


  list_for_each_entry (cur, &set_vars, node)
    {
      struct sbuf *s;
      s = sbuf_new (0);
      sbuf_copy (s, cur->var);
      list_add_tail (&s->node, list);
    }

  return list;
}
