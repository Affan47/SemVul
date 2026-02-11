gsidca_instances_added_cb(GncSxInstanceModel *model, SchedXaction *sx_added, gpointer user_data)
{
    GncSxInstanceDenseCalAdapter *adapter = GNC_SX_INSTANCE_DENSE_CAL_ADAPTER(user_data);
    g_debug("instance added\n");
    if (xaccSchedXactionGetEnabled(sx_added))
    {
        g_signal_emit_by_name(adapter, "added", GPOINTER_TO_UINT(sx_added));
    }
}
