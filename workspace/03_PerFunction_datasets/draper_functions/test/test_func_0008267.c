colon_completions (char* str UNUSED)
{
  int i;
  struct user_command *uc;
  struct sbuf *s;
  struct list_head *list;


  list = xmalloc (sizeof (struct list_head));
  INIT_LIST_HEAD (list);


  for(i=0; i<alias_list_last; ++i)
    {
      s = sbuf_new (0);
      sbuf_copy (s, alias_list[i].name);


      sbuf_concat (s, " ");
      list_add_tail (&s->node, list);
    }


  list_for_each_entry (uc, &user_commands, node)
    {
      s = sbuf_new (0);
      sbuf_copy (s, uc->name);


      sbuf_concat (s, " ");
      list_add_tail (&s->node, list);
    }

  return list;
}
