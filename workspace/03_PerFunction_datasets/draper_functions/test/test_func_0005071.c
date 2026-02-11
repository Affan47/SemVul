book_tree_find_book (DhBookTree        *tree,
                     DhBook            *book,
                     const GtkTreeIter *first,
                     GtkTreeIter       *exact_iter,
                     gboolean          *exact_found,
                     GtkTreeIter       *next_iter,
                     gboolean          *next_found)
{
        DhBookTreePriv *priv = GET_PRIVATE (tree);
        GtkTreeIter     loop_iter;

        g_assert ((exact_iter && exact_found) || (next_iter && next_found));


        if (exact_found)
                *exact_found = FALSE;
        if (next_found)
                *next_found = FALSE;


        if (!first) {

                if (!gtk_tree_model_get_iter_first (GTK_TREE_MODEL (priv->store),
                                                    &loop_iter)) {

                        return;
                }
        } else {
                loop_iter = *first;
        }

        do {
                DhBook *in_tree_book = NULL;

                gtk_tree_model_get (GTK_TREE_MODEL (priv->store),
                                    &loop_iter,
                                    COL_BOOK, &in_tree_book,
                                    -1);


                if (exact_iter &&
                    in_tree_book == book) {
                        *exact_iter = loop_iter;
                        *exact_found = TRUE;
                        if (!next_iter) {

                                g_object_unref (in_tree_book);
                                return;
                        }
                } else if (next_iter &&
                           dh_book_cmp_by_title (in_tree_book, book) > 0) {
                        *next_iter = loop_iter;
                        *next_found = TRUE;
                        g_object_unref (in_tree_book);
                        return;
                }

                if (in_tree_book)
                        g_object_unref (in_tree_book);
        } while (gtk_tree_model_iter_next (GTK_TREE_MODEL (priv->store),
                                           &loop_iter));
}
