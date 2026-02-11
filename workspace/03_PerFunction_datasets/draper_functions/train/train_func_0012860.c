declaration_alive_merge1(struct stmt *s0, struct stmt *s1)
{
	struct decl_live *l;
	int done;

	done = 1;

	for (l = s1->decl_live_first[0]; l; l = l->next) {
		done &= decl_live_add(s0, 1, l->decl);
	}

	return done;
}
