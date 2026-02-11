fa_example(struct fa *fa, char **example, size_t *example_len) {
    struct re_str *word = NULL;
    struct state_set *path = NULL, *worklist = NULL;
    struct re_str *str = NULL;

    *example = NULL;
    *example_len = 0;


    sort_transition_intervals(fa);


    path = state_set_init(-1, S_DATA|S_SORTED);
    str = make_re_str("");
    if (path == NULL || str == NULL)
        goto error;
    F(state_set_push_data(path, fa->initial, str));
    str = NULL;


    worklist = state_set_init(-1, S_NONE);
    if (worklist == NULL)
        goto error;
    F(state_set_push(worklist, fa->initial));

    while (worklist->used) {
        struct state *s = state_set_pop(worklist);
        struct re_str *ps = state_set_find_data(path, s);
        for_each_trans(t, s) {
            char c = pick_char(t);
            int toind = state_set_index(path, t->to);
            if (toind == -1) {
                struct re_str *w = string_extend(NULL, ps, c);
                E(w == NULL);
                F(state_set_push(worklist, t->to));
                F(state_set_push_data(path, t->to, w));
            } else {
                path->data[toind] = string_extend(path->data[toind], ps, c);
            }
        }
    }

    for (int i=0; i < path->used; i++) {
        struct state *p = path->states[i];
        struct re_str *ps = path->data[i];
        if (p->accept &&
            (word == NULL || word->len == 0
             || (ps->len > 0 && str_score(word) > str_score(ps)))) {
            free_re_str(word);
            word = ps;
        } else {
            free_re_str(ps);
        }
    }
    state_set_free(path);
    state_set_free(worklist);
    if (word != NULL) {
        *example_len = word->len;
        *example = word->rx;
        free(word);
    }
    return 0;
 error:
    state_set_free(path);
    state_set_free(worklist);
    free_re_str(word);
    free_re_str(str);
    return -1;
}
