put_store(struct lens *lens, struct state *state) {
    if (state->value == NULL) {
        put_error(state, lens,
                  "Can not store a nonexistent (NULL) value");
    } else if (regexp_match(lens->regexp, state->value, strlen(state->value),
                            0, NULL) != strlen(state->value)) {
        char *pat = regexp_escape(lens->regexp);
        put_error(state, lens,
                  "Value '%s' does not match regexp /%s/ in store lens",
                  state->value, pat);
        free(pat);
    } else {
        fprintf(state->out, "%s", state->value);
    }
}
