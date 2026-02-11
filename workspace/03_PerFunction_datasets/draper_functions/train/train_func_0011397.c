search_stm_directive(Block *bpt, Directive_id dir_id)
{
	Block *b;
	for (b = bpt; b != NULL; b = b->next) {
		if (b->pre_head == NULL) continue;
		Statement *s;
		for (s = b->pre_head->stm_head; s != NULL; s = s->next) {
			Directive *d;
			for (d = s->dir_pre_head; d != NULL; d = d->next) {
				Directive_func *df;
				for (df = d->func; df != NULL; df = df->next) {
					if (df->id == dir_id) {
						return s;
					}
				}
			}
		}
	}

	fatal("directive not found\n");
}
