apply_power_supply_control(Layer_info *layer_info,
                           Scheduling_info *sche)
{
    int task_num = list_length(layer_info_get_block_info_list(layer_info));

    set_start_and_end_time_in_scheduling_info(sche, sche, TRUE);

    insert_shadow_of_occupied_task(sche, sche, task_num);

    if (!is_contain_acc_conflict(layer_info->block_info_list)
        && !low_power_no_control_fv)
        set_sleep_task_in_scheduling_info(sche, layer_info);

    set_dline_control_timer_w_scheduling_info(sche, layer_info);

    set_ids_for_sleep_task_cpu(sche->sche_task_array[PROC_CPU], layer_info);
}
