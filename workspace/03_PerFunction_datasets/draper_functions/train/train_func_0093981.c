Boundary_Interval_create(gint query_pos,
                                                   gint seed_id){
    register Boundary_Interval *interval = g_new(Boundary_Interval, 1);
    interval->query_pos = query_pos;
    interval->length = 1;
    interval->seed_id = seed_id;
    return interval;
    }
