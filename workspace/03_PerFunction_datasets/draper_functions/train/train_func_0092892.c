dfs_traverse (GeglVisitor   *self,
              GeglVisitable *visitable)
{
  GSList *depends_on_list;
  GSList *llink;

  depends_on_list = gegl_visitable_depends_on (visitable);
  llink           = depends_on_list;

  while (llink)
    {
      GeglVisitable *visitable = llink->data;


      if (!get_visited (self, visitable))
        dfs_traverse (self, visitable);

      llink = g_slist_next (llink);
    }

  g_slist_free (depends_on_list);


  gegl_visitable_accept (visitable, self);

  set_visited (self, visitable, TRUE);
}
