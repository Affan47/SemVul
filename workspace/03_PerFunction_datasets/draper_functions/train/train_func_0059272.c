gnc_sx_get_instances(const GDate *range_end, gboolean include_disabled)
{
    GList *all_sxes = gnc_book_get_schedxactions(gnc_get_current_book())->sx_list;
    GncSxInstanceModel *instances;

    g_assert(range_end != NULL);
    g_assert(g_date_valid(range_end));

    instances = gnc_sx_instance_model_new();
    instances->include_disabled = include_disabled;
    instances->range_end = *range_end;

    if (include_disabled)
    {
        instances->sx_instance_list = gnc_g_list_map(all_sxes, (GncGMapFunc)_gnc_sx_gen_instances, (gpointer)range_end);
    }
    else
    {
        GList *sx_iter = g_list_first(all_sxes);
        GList *enabled_sxes = NULL;

        for (; sx_iter != NULL; sx_iter = sx_iter->next)
        {
            SchedXaction *sx = (SchedXaction*)sx_iter->data;
            if (xaccSchedXactionGetEnabled(sx))
            {
                enabled_sxes = g_list_append(enabled_sxes, sx);
            }
        }
        instances->sx_instance_list = gnc_g_list_map(enabled_sxes, (GncGMapFunc)_gnc_sx_gen_instances, (gpointer)range_end);
        g_list_free(enabled_sxes);
    }

    return instances;
}
