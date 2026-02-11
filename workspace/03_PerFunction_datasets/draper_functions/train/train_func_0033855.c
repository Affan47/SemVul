generic_timespec_start_handler(GSList* sibling_data, gpointer parent_data,
                               gpointer global_data,
                               gpointer *data_for_children, gpointer *result,
                               const gchar *tag, gchar **attrs)
{
    TimespecParseInfo *tsp = g_new0(TimespecParseInfo, 1);
    g_return_val_if_fail(tsp, FALSE);
    *data_for_children = tsp;
    return(TRUE);
}
