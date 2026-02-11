iter_to_string (GtkTreeIter *iter)
{
    gnc_commodity_namespace *namespace;
    gnc_commodity *commodity = NULL;
#ifdef G_THREADS_ENABLED
#ifndef HAVE_GLIB_2_32
    static GStaticPrivate gtmits_buffer_key = G_STATIC_PRIVATE_INIT;
    gchar *string;

    string = g_static_private_get (&gtmits_buffer_key);
    if (string == NULL)
    {
        string = g_malloc(ITER_STRING_LEN + 1);
        g_static_private_set (&gtmits_buffer_key, string, g_free);
    }
#else
    static GPrivate gtmits_buffer_key = G_PRIVATE_INIT(g_free);
    gchar *string;

    string = g_private_get (&gtmits_buffer_key);
    if (string == NULL)
    {
        string = g_malloc(ITER_STRING_LEN + 1);
        g_private_set (&gtmits_buffer_key, string);
    }
#endif
#else
    static char string[ITER_STRING_LEN + 1];
#endif
    if (iter)
    {
        switch (GPOINTER_TO_INT(iter->user_data))
        {
        case GPOINTER_TO_INT(ITER_IS_NAMESPACE):
            namespace = (gnc_commodity_namespace *) iter->user_data2;
            snprintf(string, ITER_STRING_LEN,
                     "[stamp:%x data:%d (NAMESPACE), %p (%s), %d]",
                     iter->stamp, GPOINTER_TO_INT(iter->user_data),
                     iter->user_data2, gnc_commodity_namespace_get_name (namespace),
                     GPOINTER_TO_INT(iter->user_data3));
            break;

        case GPOINTER_TO_INT(ITER_IS_COMMODITY):
            commodity = (gnc_commodity *) iter->user_data2;
            snprintf(string, ITER_STRING_LEN,
                     "[stamp:%x data:%d (COMMODITY), %p (%s), %d]",
                     iter->stamp, GPOINTER_TO_INT(iter->user_data),
                     iter->user_data2, gnc_commodity_get_mnemonic (commodity),
                     GPOINTER_TO_INT(iter->user_data3));
            break;

        default:
            snprintf(string, ITER_STRING_LEN,
                     "[stamp:%x data:%d (UNKNOWN), %p, %d]",
                     iter->stamp,
                     GPOINTER_TO_INT(iter->user_data),
                     iter->user_data2,
                     GPOINTER_TO_INT(iter->user_data3));
            break;
        }
    }
    return string;
}
