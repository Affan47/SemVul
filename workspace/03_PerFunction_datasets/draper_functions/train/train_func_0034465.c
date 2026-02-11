set_fv_cost_by_block_param(Ctrl_task *ctrl_task)
{
    real cost, p_cost, d_energy, s_energy, p_energy;
    Block_info *b_info = ctrl_task_get_b_info(ctrl_task);
    Block *block = block_info_get_block(b_info);
    int pe_num = get_pe_num_of_parallel_loop(block);
    proc_kind proc = block_info_get_proc(b_info);
    Low_power_param *param;
    int acc_tp;

    fv_kind fv = ctrl_task_get_fv(ctrl_task);
    if(proc == PROC_ACC && block->acc_block != NULL) block = block->acc_block;


    cost = ctrl_task_get_fv_cost(ctrl_task, fv)
        + block_info_get_cost(b_info, FULL) / pe_num;
    p_cost = 0;

    d_energy = block_info_get_energy(b_info, fv) / pe_num;
    s_energy = block_info_get_s_energy(b_info, fv);
    p_energy = 0;

    if (ctrl_task_insert_fv(ctrl_task)) {

        fv_kind prev_fv = (fv != FULL) ? FULL : MID;
        acc_tp = block_info_get_acc_tp(b_info);
        param = get_one_lp_param(proc, acc_tp);
        p_cost = param->delay_penalty[prev_fv][fv];
        p_energy = param->energy_penalty[prev_fv][fv];
    }

    ctrl_task_set_fv_cost(ctrl_task, fv, cost);
    ctrl_task_set_fv_mask(ctrl_task, fv, TRUE);
    ctrl_task_set_fv_p_cost(ctrl_task, p_cost);
    ctrl_task_set_energy(ctrl_task, d_energy + s_energy + p_energy);

    return (pe_num == 1);
}
