del_entry_type(struct user_entry_type *type)
{
  struct userrec *u;

  for (u = userlist; u; u = u->next) {
    struct user_entry *e = find_user_entry(type, u);

    if (e && !e->name) {
      e->type->pack(u, e);
      e->name = user_malloc(strlen(e->type->name) + 1);
      strcpy(e->name, e->type->name);
      e->type = NULL;
    }
  }
  return list_delete((struct list_type **) &entry_type_list,
                     (struct list_type *) type);
}
