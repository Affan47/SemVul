inf_adopted_undo_grouping_add_request(InfAdoptedUndoGrouping* grouping,
                                      InfAdoptedRequest* request)
{
  InfAdoptedUndoGroupingPrivate* priv;
  guint max;
  InfAdoptedUndoGroupingItem* item;
  InfAdoptedUndoGroupingItem* prev_item;

  InfAdoptedUndoGroupingFlags flags;
  gboolean first_after_group;
  gboolean first_in_group;
  gboolean allow_with_next;
  gboolean allow_with_prev;

  priv = INF_ADOPTED_UNDO_GROUPING_PRIVATE(grouping);

  switch(inf_adopted_request_get_request_type(request))
  {
  case INF_ADOPTED_REQUEST_DO:
    if(priv->first_item + priv->item_pos == priv->n_alloc)
    {


      g_object_get(
        G_OBJECT(priv->algorithm),
        "max-total-log-size", &max,
        NULL
      );

      if(max != G_MAXUINT)
      {
        max = (max/2) + 1;


        if(priv->n_alloc < max)
        {
          priv->n_alloc = MIN(priv->n_alloc * 2, max);
          priv->n_alloc = MAX(priv->n_alloc, MIN(16, max));

          priv->items = g_realloc(
            priv->items,
            priv->n_alloc * sizeof(InfAdoptedUndoGroupingItem)
          );
        }
      }
      else
      {
        priv->n_alloc = MAX(priv->n_alloc * 2, 16);

        priv->items = g_realloc(
          priv->items,
          priv->n_alloc * sizeof(InfAdoptedUndoGroupingItem)
        );
      }
    }


    priv->n_items = priv->item_pos;
    g_assert(priv->n_items < priv->n_alloc);
    item = &priv->items[(priv->first_item + priv->item_pos) % priv->n_alloc];


    item->request = request;

    if(priv->item_pos > 0)
    {
      flags = priv->group_flags;

      first_after_group =
        (flags & INF_ADOPTED_UNDO_GROUPING_FIRST_AFTER_GROUP) != 0;
      first_in_group =
        (flags & INF_ADOPTED_UNDO_GROUPING_FIRST_IN_GROUP) != 0;
      allow_with_next =
        (flags & INF_ADOPTED_UNDO_GROUPING_ALLOW_WITH_NEXT) != 0;
      allow_with_prev =
        (flags & INF_ADOPTED_UNDO_GROUPING_ALLOW_WITH_PREV) != 0;

      if(first_after_group && !allow_with_next)
      {
        item->in_group = FALSE;
      }
      else if(priv->group_ref > 0 && first_in_group && !allow_with_prev)
      {
        item->in_group = FALSE;
      }
      else if(priv->group_ref > 0 && !first_in_group)
      {
        item->in_group = TRUE;
      }
      else
      {
        prev_item = &priv->items[
          (priv->first_item + priv->item_pos - 1) % priv->n_alloc
        ];

        g_signal_emit(
          G_OBJECT(grouping),
          undo_grouping_signals[GROUP_REQUESTS],
          0,
          prev_item->request,
          request,
          &item->in_group
        );
      }
    }
    else
    {

      item->in_group = FALSE;
    }

    priv->group_flags &= ~(INF_ADOPTED_UNDO_GROUPING_FIRST_IN_GROUP |
                           INF_ADOPTED_UNDO_GROUPING_FIRST_AFTER_GROUP);

    ++priv->n_items;
    ++priv->item_pos;
    break;
  case INF_ADOPTED_REQUEST_UNDO:
    g_assert(priv->item_pos > 0);
    --priv->item_pos;
    break;
  case INF_ADOPTED_REQUEST_REDO:
    g_assert(priv->item_pos < priv->n_items);
    ++priv->item_pos;
    break;
  }
}
