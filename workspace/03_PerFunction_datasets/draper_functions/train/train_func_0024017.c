xaccSchedXactionSetNumOccur(SchedXaction *sx, gint new_num)
{
    if (sx->num_occurances_total == new_num)
        return;
    gnc_sx_begin_edit(sx);
    sx->num_occurances_remain = sx->num_occurances_total = new_num;
    qof_instance_set_dirty(&sx->inst);
    gnc_sx_commit_edit(sx);
}
