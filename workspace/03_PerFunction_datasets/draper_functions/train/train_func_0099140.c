group_delete_group (rp_group *g)
{
  if (list_empty (&(g->mapped_windows))
      && list_empty (&(g->unmapped_windows)))
    {

      if (list_size (&rp_groups) == 1)
        return GROUP_DELETE_LAST_GROUP;


      if (g == rp_current_group)
        {
          rp_group *next = group_last_group ();
          set_current_group (next ? next : group_next_group ());
        }

      list_del (&(g->node));
      group_free (g);
      return GROUP_DELETE_GROUP_OK;
    }
  else
    {
      return GROUP_DELETE_GROUP_NONEMPTY;
    }
}
