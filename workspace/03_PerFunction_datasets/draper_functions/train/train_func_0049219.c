subtract_id_trans(Stasche *sinfo, int dstpcno, int srcmtno, int dstmtno,
                  Array_def_use_table_semnode *apt)
{
    int i;
    Boolean unknown;
    int *ntasks = sinfo->ntasks;
    int **sched = sinfo->sched;
    Array_def_use_table_semnode *id;

    for (i = sinfo->onlmtasks[dstpcno]; i < ntasks[dstpcno]; i++) {
        int prev_mt = sched[dstpcno][i];
        if (in_IntSet(sinfo->block[prev_mt]->pred, srcmtno)) {
            IntSet local_array;
            if (flg_lad_ya_templ) {
                if (sinfo->block[prev_mt]->cmp_localize != NULL) {
                    local_array = sinfo->block[prev_mt]->cmp_localize->local_array;
                    id = copy_array_def_use_table_semnode(
                        get_array_use_use(sinfo->block[prev_mt],
                                          sinfo->block[dstmtno]));
                    id = select_array_du_semnode(id, local_array, NULL, NULL);
                } else {
                    id = NULL;
                }
            } else {
                id = get_array_use_use(sinfo->block[prev_mt], sinfo->block[dstmtno]);
            }

            apt = subtract_array_def_use_table_semnode(sinfo->module,
                                                       apt,
                                                       id,
                                                       &unknown);
            if (flg_lad_ya_templ) {
                free_all_array_def_use_table_semnode(id);
            }
        }
    }
    return apt;
}
