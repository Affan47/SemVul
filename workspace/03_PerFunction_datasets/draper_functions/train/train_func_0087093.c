append_macro_to_list_store(GtkListStore* list, CMacroTable macro)
{
    GtkTreeIter iter;
    gchar key[MAX_MACRO_KEY_LEN*3];
    gchar value[MAX_MACRO_TEXT_LEN*3];
    gchar* oldkey;
    UKBYTE* p;
    int inLen, maxOutLen;
    int i, ret;

    for (i = 0 ; i < macro.getCount(); i++)
    {

        p = (UKBYTE*)macro.getKey(i);
        inLen = -1;
        maxOutLen = sizeof(key);
        ret = VnConvert(CONV_CHARSET_VNSTANDARD, CONV_CHARSET_XUTF8,
                        p, (UKBYTE*)key,
                        &inLen, &maxOutLen);
        if (ret != 0)
            continue;


        gboolean b = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(list), &iter);
        while (b)
        {
            gtk_tree_model_get(GTK_TREE_MODEL(list), &iter, COL_KEY, &oldkey, -1);

            if (strcasecmp(oldkey, key) == 0)
            {
                break;
            }

            b = gtk_tree_model_iter_next(GTK_TREE_MODEL(list), &iter);
        }
        if (b)
        {
            continue;
        }


        p = (UKBYTE*)macro.getText(i);
        inLen = -1;
        maxOutLen = sizeof(value);
        ret = VnConvert(CONV_CHARSET_VNSTANDARD, CONV_CHARSET_XUTF8,
                        p, (UKBYTE*)value,
                        &inLen, &maxOutLen);
        if (ret != 0)
            continue;


        gtk_list_store_append(list, &iter);
        gtk_list_store_set(list, &iter, COL_KEY, key, COL_VALUE, value, -1);
    }
}
