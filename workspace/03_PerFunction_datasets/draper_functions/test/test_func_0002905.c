xaccSchedXactionSetLastOccurDate(SchedXaction *sx, const GDate* new_last_occur)
{
    if (g_date_valid(&sx->last_date)
            && g_date_compare(&sx->last_date, new_last_occur) == 0)
        return;
    gnc_sx_begin_edit(sx);
    sx->last_date = *new_last_occur;
    qof_instance_set_dirty(&sx->inst);
    gnc_sx_commit_edit(sx);
}
