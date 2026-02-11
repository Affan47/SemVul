Scheduler_SpanSeed_copy(Scheduler_SpanSeed *src,
                                    Scheduler_SpanSeed *dst,
                                    Scheduler_Pair *spair){
    register gint i;
    register C4_Model *model = spair->scheduler->model;
    g_assert(src);
    g_assert(dst);
    dst->score        = src->score;
    dst->max          = src->max;
    dst->seed_id      = src->seed_id;
    dst->query_entry  = src->query_entry;
    dst->target_entry = src->target_entry;
    STraceback_Cell_destroy(dst->cell, spair->straceback);
    dst->cell = STraceback_Cell_share(src->cell);

    if(spair->scheduler->is_forward)
        for(i = 0; i < model->total_shadow_designations; i++)
            dst->shadow_data[i] = src->shadow_data[i];
    return;
    }
