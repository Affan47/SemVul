gegl_path_list_append_item  (GeglPathList  *head,
                             gchar          type,
                             GeglPathList **res,
                             GeglPathList  *tail)
{
  GeglPathList *iter = tail?tail:head;
  InstructionInfo *info = lookup_instruction_info (type);
  g_assert (info);

  while (iter && iter->next)
    iter=iter->next;

  if (iter)
    {

      iter->next =
        g_slice_alloc0 (sizeof (gpointer) + sizeof (gchar) + sizeof (gfloat)*2 *(info->n_items+3)/2);
      iter->next->d.type = type;
      iter = iter->next;
    }
  else
    {

      head =
        g_slice_alloc0 (sizeof (gpointer) + sizeof (gchar) + sizeof (gfloat)*2 *(info->n_items+3)/2);
      head->d.type = type;
      iter=head;
    }
  g_assert (res);
  *res = iter;

  return head;
}
