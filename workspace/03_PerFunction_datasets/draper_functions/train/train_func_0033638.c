real_players_dialog_update(void)
{
  GtkTreeModel *model;
  GtkTreeIter iter;
  int selected;

  if (NULL == players_dialog_shell) {
    return;
  }


  if (gtk_tree_selection_get_selected(players_selection, &model, &iter)) {
    gtk_tree_model_get(model, &iter, PLR_DLG_COL_ID, &selected, -1);
  } else {
    selected = -1;
  }

  gtk_list_store_clear(players_dialog_store);
  players_iterate(pplayer) {
    if (!player_should_be_shown(pplayer)) {
      continue;
    }
    gtk_list_store_append(players_dialog_store, &iter);
    fill_row(players_dialog_store, &iter, pplayer);
    if (player_number(pplayer) == selected) {

      gtk_tree_selection_select_iter(players_selection, &iter);
    }
  } players_iterate_end;

  update_views();
}
