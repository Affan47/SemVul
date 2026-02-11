free_state(struct state *s) {
    if (s == NULL)
        return;
    free(s->ret);
    array_release(&s->trans);
    free(s);
}
