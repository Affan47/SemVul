get_path_for_cfpre_block(Block_info *block_info, Path *pred_path)
{
    Path *path;
    Boolean certain_length, certain_energy;
    real cost[FV_STATE_NUM];
    real cf_min_length[FV_STATE_NUM];
    real sche_length[FV_STATE_NUM];
    real energy[FV_STATE_NUM];
    real s_energy[FV_STATE_NUM];
    fv_kind fv;

    int id = block_info_get_id(block_info);
    int nest = 1;
    int *nested_id = copy_int_vector(&id, nest);
    proc_kind proc = block_info_get_proc(block_info);
    int acc_tp = block_info_get_acc_tp(block_info);

    Term *term = term_new(id, copy_int_vector(nested_id, nest), nest,
                          SINGLE, proc, acc_tp, block_info, TRUE);
    List *term_list;

    term_list = term_list_copy(path_get_term_list(pred_path));
    term_list = list_append(term_list, term);

    certain_length = path_is_certain_length(pred_path)
        && block_info_is_certain_length(block_info);

    certain_energy = path_is_certain_energy(pred_path)
        && block_info_is_certain_energy(block_info);

    path = path_new(id, nested_id, nest,
                    proc, acc_tp, term_list,
                    certain_length, certain_energy);

    for (fv = FULL; fv <= SLOWEST_FV; fv++) {
        real prob = block_info_get_branch_prob(block_info);

        cost[fv] = path_get_cost(pred_path, fv)
            + block_info_get_cost(block_info, fv) * prob;

        sche_length[fv] = path_get_sche_length(pred_path, fv)
            + block_info_get_sche_length(block_info, fv);

        cf_min_length[fv] = path_get_cf_min_length(pred_path, fv)
            + block_info_get_cf_min_length(block_info, fv);

        energy[fv] = path_get_energy(pred_path, fv)
            + block_info_get_energy(block_info, fv) * prob;

        s_energy[fv] = path_get_s_energy(pred_path, fv)
            + block_info_get_s_energy(block_info, fv) * prob;
    }

    for (fv = FULL; fv <= SLOWEST_FV; fv++) {
        path_set_cost(path, fv, cost[fv]);
        path_set_sche_length(path, fv, sche_length[fv]);
        path_set_cf_min_length(path, fv, cf_min_length[fv]);
        path_set_energy(path, fv, energy[fv]);
        path_set_s_energy(path, fv, s_energy[fv]);
    }

    return path;
}
