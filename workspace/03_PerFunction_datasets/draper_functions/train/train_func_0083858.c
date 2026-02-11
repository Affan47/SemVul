Scheduler_Cache_fill_func(gint start,
                                                   gpointer user_data){
    register Scheduler_Pair *spair = user_data;
    register Scheduler_SpanSeed ***seed_matrix
          = (Scheduler_SpanSeed***)Matrix2d_create(
                         SparseCache_PAGE_SIZE,
                         spair->scheduler->model->span_list->len,
                         sizeof(Scheduler_SpanSeed*));
    register SparseCache_Page *page = g_new(SparseCache_Page, 1);
    page->data = seed_matrix;
    page->data_size = Matrix2d_size(SparseCache_PAGE_SIZE,
                                    spair->scheduler->model->span_list->len,
                                    sizeof(Scheduler_SpanSeed*));
    page->get_func = Scheduler_Cache_get_func;
    page->copy_func = NULL;
    return page;
    }
