Scheduler_Seed_List_next_reverse(gpointer seed_data){
    register Scheduler_Seed_List *seed_info_list = seed_data;
    g_assert(seed_info_list);
    g_assert(seed_info_list->seed_pos >= 0);
    seed_info_list->seed_pos--;
    return;
    }
