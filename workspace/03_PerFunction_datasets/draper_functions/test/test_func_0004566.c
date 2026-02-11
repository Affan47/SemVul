plps_sym_cmp_localize(Task *task)
{
    Block *target = task->block[task->SelectTask];
    Array_entry_dtu_params **eparams;
    Dtu_mt **dtu_mt;
    int amax = get_max_array_entry(target->module->array_head);
    int i;

    eparams = plps_sym_mng_lm_and_calc_dt(task, target);

    dtu_mt = calloc(amax + 1, sizeof(Dtu_mt*));
    if (dtu_mt == NULL) {
        fatal("No room\n");
    }

    for (i = 1; i <= amax; i++) {
        dtu_mt[i] = plps_sym_possible_dt_timing(task, target, eparams[i], i);
    }

    for (i = 1; i <= amax; i++) {
        plps_sym_simple_set_dt_timing(task, target, eparams[i], dtu_mt[i]);
    }
}
