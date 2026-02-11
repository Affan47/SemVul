check_new_and_strlen(struct state *st, const char *const p) {
    if(check_new(st, p))
	st->total_size += 1 + strlen(p);
}
