simplify_split_vardecl_init(struct stmt *s)
{
	struct stmt *cs;
	int retval;

	retval = 0;

	if (s->stmt0) {
		retval |= simplify_split_vardecl_init(s->stmt0);
	}
	if (s->stmt1) {
		retval |= simplify_split_vardecl_init(s->stmt1);
	}
	for (cs = s->stmt_first; cs; cs = cs->next) {
		retval |= simplify_split_vardecl_init(cs);
	}

	if (s->type == STMT_BLOCK) {
		struct declaration *dion;

		for (dion = s->scope->declaration_last;
		    dion;
		    dion = dion->prev) {
			if (dion->storage == STORAGE_NONE
			 || dion->storage == STORAGE_AUTO
			 || dion->storage == STORAGE_REGISTER) {
				struct expr *initializer;

				initializer = declaration_initializer_get(dion);

				if (initializer) {
					struct stmt *s0;

					declaration_initializer_set(dion,
							NULL);


					dion->type_name->mod_const = 0;

					s0 = stmt_expr(expr_assign(
							expr_identifier(dion),
							initializer));

					stmt_prepend(s, s->stmt_first, s0);
					retval |= 1;
				}
			}
		}
	}

	return retval;
}
