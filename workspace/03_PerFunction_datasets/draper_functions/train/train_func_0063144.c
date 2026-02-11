gtr_message_table_selection_changed (GtkTreeSelection *selection,
                                     GtrMessageTable *table)
{
  GtkTreeIter iter;
  GtkTreeModel *model;
  GtrMsg *msg;
  GList *current_msg = NULL;
  GtrPo *po;

  g_return_if_fail (selection != NULL);

  po = gtr_tab_get_po (table->priv->tab);
  current_msg = gtr_po_get_current_message (po);

  if (gtk_tree_selection_get_selected (selection, &model, &iter) == TRUE)
    {
      gtk_tree_model_get (model, &iter,
                          GTR_MESSAGE_TABLE_MODEL_POINTER_COLUMN, &msg, -1);

      if (msg != NULL
          && g_utf8_collate (gtr_msg_get_msgid (msg),
                             gtr_msg_get_msgid (current_msg->data)))
        {
          g_signal_handlers_block_by_func (table->priv->tab, showed_message_cb, table);
          gtr_tab_message_go_to (table->priv->tab, msg,
                                 FALSE, GTR_TAB_MOVE_NONE);
          g_signal_handlers_unblock_by_func (table->priv->tab, showed_message_cb, table);
        }
    }
}
