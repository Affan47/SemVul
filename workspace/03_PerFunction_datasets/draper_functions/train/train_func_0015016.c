Heuristic_Range_create(gint internal,
                                               gint external,
                                               C4_Portal *portal){
    register Heuristic_Range *heuristic_range = g_new(Heuristic_Range,
                                                      1);
    g_assert(internal);
    g_assert(external);
    heuristic_range->internal_query = internal
                                    * portal->advance_query;
    heuristic_range->internal_target = internal
                                     * portal->advance_target;
    heuristic_range->external_query = external
                                    * portal->advance_query;
    heuristic_range->external_target = external
                                     * portal->advance_target;
    return heuristic_range;
    }
