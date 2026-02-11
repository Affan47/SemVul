set_initial(struct fa *fa, struct state *s) {
    list_remove(s, fa->initial);
    list_cons(fa->initial, s);
}
