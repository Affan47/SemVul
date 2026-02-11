Combo_Alphabetic_Sort (GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer data)
{
    gchar *text1, *text1_folded;
    gchar *text2, *text2_folded;
    gint ret;

    gtk_tree_model_get(model, a, MISC_COMBO_TEXT, &text1, -1);
    gtk_tree_model_get(model, b, MISC_COMBO_TEXT, &text2, -1);

    if (text1 == text2)
    {
        g_free(text1);
        g_free(text2);
        return 0;
    }

    if (text1 == NULL)
    {
        g_free(text2);
        return -1;
    }

    if (text2 == NULL)
    {
        g_free(text1);
        return 1;
    }

    text1_folded = g_utf8_casefold(text1, -1);
    text2_folded = g_utf8_casefold(text2, -1);
    ret = g_utf8_collate(text1_folded, text2_folded);

    g_free(text1);
    g_free(text2);
    g_free(text1_folded);
    g_free(text2_folded);
    return ret;
}
