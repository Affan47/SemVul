atom_info_list_free (GList * ai)
{
  while (ai) {
    AtomInfo *info = (AtomInfo *) ai->data;

    info->free_func (info->atom);
    g_free (info);
    ai = g_list_delete_link (ai, ai);
  }
}
