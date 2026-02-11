addressbook_window_update_book (AddressBookWindow *self,
                                Ekiga::BookPtr book)
{
  GtkTreeIter iter;
  GtkTreeModel *store = NULL;

  store = gtk_tree_view_get_model (GTK_TREE_VIEW (self->priv->tree_view));
  if (find_iter_for_book (self, book, &iter))
    gtk_tree_store_set (GTK_TREE_STORE (store), &iter,
                        COLUMN_NAME, book->get_name ().c_str (),
                        -1);
}
