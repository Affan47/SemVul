Scheduler_create(C4_Model *model,
                      gboolean is_forward, gboolean has_traceback,
                      gboolean use_boundary,
                      Scheduler_Seed_init_Func init_func,
                      Scheduler_Seed_next_Func next_func,
                      Scheduler_Seed_get_Func get_func,
                      Scheduler_start_Func start_func,
                      Scheduler_end_Func end_func,
                      C4_Score dropoff){
    register Scheduler *scheduler = g_new(Scheduler, 1);
    register gchar *raw_name;
    register Codegen_ArgumentSet *cas
           = Codegen_ArgumentSet_create(NULL);
    g_assert(!(is_forward && start_func));
    g_assert(!(use_boundary && start_func));
    g_assert(!((!is_forward) && end_func));
    scheduler->is_forward = is_forward;
    scheduler->has_traceback = has_traceback;
    scheduler->use_boundary = use_boundary;

    scheduler->shadow_start = 3;
    scheduler->cell_score_offset = sizeof(Scheduler_Cell);
    scheduler->cell_traceback_offset = scheduler->cell_score_offset
                        + Matrix2d_size(model->state_list->len,
                                        scheduler->shadow_start
                                        + model->shadow_list->len,
                                        sizeof(C4_Score));
    scheduler->cell_size = scheduler->cell_traceback_offset;
    if(has_traceback)
        scheduler->cell_size += (sizeof(STraceback_Cell*)
                                 * model->state_list->len);
    scheduler->init_func = init_func;
    scheduler->next_func = next_func;
    scheduler->get_func = get_func;
    scheduler->start_func = start_func;
    scheduler->end_func = end_func;
    scheduler->model = C4_Model_share(model);
    scheduler->span_map = Scheduler_get_span_map(model);
    scheduler->dropoff = dropoff;

    raw_name = g_strdup_printf("Scheduler_Cell_process_%s:%s:%s:%s",
                               model->name,
                               is_forward?"forward":"reverse",
                               has_traceback?"traceback":"notraceback",
                               use_boundary?"boundary":"seeded");
    scheduler->name = Codegen_clean_path_component(raw_name);
    g_free(raw_name);
    if(cas->use_compiled){
#ifdef USE_COMPILED_MODELS
        scheduler->cell_func
            = (Scheduler_DP_Func)Bootstrapper_lookup(scheduler->name);
        if(!scheduler->cell_func){
            g_warning("Could not find compiled implementation of [%s]",
                    scheduler->name);
            scheduler->cell_func = Scheduler_Cell_process;
            }
#else
        g_warning("No compiled models - will be very slow");
        scheduler->cell_func = Scheduler_Cell_process;
#endif
    } else {
        scheduler->cell_func = Scheduler_Cell_process;
        }
    g_assert(scheduler->cell_func);
    return scheduler;
    }
