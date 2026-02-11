rewriteConfigGetContentFromState(struct rewriteConfigState *state) {
    sds content = sdsempty();
    int j, was_empty = 0;

    for (j = 0; j < state->numlines; j++) {

        if (sdslen(state->lines[j]) == 0) {
            if (was_empty) continue;
            was_empty = 1;
        } else {
            was_empty = 0;
        }
        content = sdscatsds(content,state->lines[j]);
        content = sdscatlen(content,"\n",1);
    }
    return content;
}
