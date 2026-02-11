C4_Model_path_is_possible(C4_Model *model,
                                   C4_State *src, C4_State *dst){
    register gboolean *visited;
    register gboolean is_valid;
    g_assert(model);
    g_assert(src);
    g_assert(dst);
    visited = g_new0(gboolean, model->state_list->len);
    is_valid = C4_Model_path_is_possible_recur(model, src, dst,
                                               visited);
    g_free(visited);
    return is_valid;
    }
