exo_tree_view_set_single_click_timeout (ExoTreeView *tree_view,
                                        guint        single_click_timeout)
{
  g_return_if_fail (EXO_IS_TREE_VIEW (tree_view));


  if (tree_view->priv->single_click_timeout != single_click_timeout)
    {

      tree_view->priv->single_click_timeout = single_click_timeout;


      if (G_UNLIKELY (tree_view->priv->single_click_timeout_id >= 0))
        g_source_remove (tree_view->priv->single_click_timeout_id);


      g_object_notify (G_OBJECT (tree_view), "single-click-timeout");
    }
}
