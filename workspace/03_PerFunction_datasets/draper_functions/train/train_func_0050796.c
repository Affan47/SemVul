cb_complete_run (CutRunContext *pipeline, gboolean success, gpointer user_data)
{
    CutSubProcessGroup *group = user_data;
    CutSubProcessGroupPrivate *priv;

    priv = CUT_SUB_PROCESS_GROUP_GET_PRIVATE(group);
    priv->n_uncompleted_processes--;
    if (!success)
        priv->all_success = FALSE;

    g_signal_handlers_disconnect_by_func(pipeline,
                                         (GFunc)cb_complete_run,
                                         user_data);
}
