parse_concat(struct lens *lens, struct state *state,
                                 struct dict **dict) {
    ensure0(lens->tag == L_CONCAT, state->info);
    struct skel *skel = make_skel(lens);
    uint old_nreg = state->nreg;

    state->nreg += 1;
    for (int i=0; i < lens->nchildren; i++) {
        struct skel *sk = NULL;
        struct dict *di = NULL;
        if (! REG_VALID(state)) {
            get_error(state, lens->children[i],
                      "Not enough components in concat");
            free_skel(skel);
            return NULL;
        }

        sk = parse_lens(lens->children[i], state, &di);
        list_append(skel->skels, sk);
        dict_append(dict, di);
        state->nreg += 1 + regexp_nsub(lens->children[i]->ctype);
    }
    state->nreg = old_nreg;

    return skel;
}
