fa_merge(struct fa *fa1, struct fa **fa2) {
    list_append(fa1->initial, (*fa2)->initial);
    free(*fa2);
    *fa2 = NULL;
}
