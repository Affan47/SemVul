inf_adopted_undo_grouping_end_group(InfAdoptedUndoGrouping* grouping,
                                    gboolean allow_group_with_next)
{
  InfAdoptedUndoGroupingPrivate* priv;

  g_return_if_fail(INF_ADOPTED_IS_UNDO_GROUPING(grouping));

  priv = INF_ADOPTED_UNDO_GROUPING_PRIVATE(grouping);
  g_return_if_fail(priv->algorithm != NULL);
  g_return_if_fail(priv->user != NULL);

  g_return_if_fail(priv->group_ref > 0);
  if(--priv->group_ref == 0)
  {
    priv->group_flags = INF_ADOPTED_UNDO_GROUPING_FIRST_AFTER_GROUP;
    if(allow_group_with_next)
      priv->group_flags |= INF_ADOPTED_UNDO_GROUPING_ALLOW_WITH_NEXT;
  }
}
