get_optimal_fv_for_dir_deadline_layer(Layer_info *layer_info,
                                      fv_kind outer_assigned_fv,
                                      real layer_margin)
{
    fv_kind fv, tar_fv = FULL;
    Low_power_param *param = get_one_lp_param(PROC_CPU, ACC_TYPE_NON);
    real sche_length = layer_info_get_sche_length(layer_info, FULL);
    real min_energy = layer_info_get_energy(layer_info, FULL)
        + layer_info_get_s_energy(layer_info, FULL);

    for (fv = FULL+1; fv <= SLOWEST_FV; fv++) {
        real length, penalty, energy;

        if (!layer_info->fv_mask[fv]) continue;

        length = sche_length * param->delay_rate[fv];
        penalty = (param->delay_penalty[FULL][fv]
                   + param->delay_penalty[fv][FULL]);

        energy = layer_info_get_energy(layer_info, fv)
            + layer_info_get_s_energy(layer_info, fv);

        if (length + penalty <= layer_margin && energy < min_energy) {
            min_energy = energy;
            tar_fv = fv;
        }
    }

    return (tar_fv > outer_assigned_fv) ? tar_fv : outer_assigned_fv;
}
