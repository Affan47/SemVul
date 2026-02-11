mi_end_bulk_insert(MI_INFO *info)
{
  if (info->bulk_insert)
  {
    uint i;
    for (i=0 ; i < info->s->base.keys ; i++)
    {
      if (is_tree_inited(& info->bulk_insert[i]))
      {
        delete_tree(& info->bulk_insert[i]);
      }
    }
    my_free(info->bulk_insert);
    info->bulk_insert=0;
  }
}
