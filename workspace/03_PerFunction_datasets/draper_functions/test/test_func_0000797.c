giggle_diff_view_get_current_file_nb (GiggleDiffView *diff_view)
{
       GiggleDiffViewPriv *priv;
       GiggleDiffViewHunk *hunk = NULL;

       g_return_val_if_fail (GIGGLE_IS_DIFF_VIEW (diff_view), 0);

       priv = GET_PRIV (diff_view);

       if (priv->current_hunk >= 0)
	       hunk = diff_view_get_hunk (priv, priv->current_hunk);
       if (hunk)
               return hunk->file;

       return 0;
}
