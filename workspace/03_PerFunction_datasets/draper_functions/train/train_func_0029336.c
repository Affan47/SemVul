Scheduler_Cell_add_span(STraceback_Cell *prev,
                                         STraceback *straceback,
                                         C4_Span *span,
                                         gint query_len, gint target_len){
    g_assert(span);
    g_assert(span->query_loop || (!query_len));
    g_assert(span->target_loop || (!target_len));
    if(query_len){
        g_assert(query_len >= 0);
        g_assert(span->query_loop);
        prev = STraceback_add(straceback, span->query_loop, query_len, prev);
        }
    if(target_len){
        g_assert(target_len >= 0);
        g_assert(span->target_loop);
        prev = STraceback_add(straceback, span->target_loop, target_len, prev);
        }
    return prev;
    }
