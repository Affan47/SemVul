keyword_model_iter_children (GtkTreeModel *tree_model,
                             GtkTreeIter  *iter,
                             GtkTreeIter  *parent)
{
        DhKeywordModelPriv *priv;

        priv = DH_KEYWORD_MODEL (tree_model)->priv;


        if (parent) {
                return FALSE;
        }


        if (priv->keyword_words) {
                iter->stamp = priv->stamp;
                iter->user_data = priv->keyword_words;
                return TRUE;
        }

        return FALSE;
}
