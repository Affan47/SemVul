_scope_lookup(
        struct scope *scope,
        const char *name,
        struct declaration **dorp
)
{
        struct declaration *dion;

        for (dion = scope->declaration_first; ; dion = dion->next) {
                if (! dion) {

                        return -1;
                }
		if (dion->type_name
		 && dion->type_name->type == TYPE_ENUM
		 && dion->type_name->scope) {
			int ret;

			ret = _scope_lookup_enum(
					dion->type_name->scope, name,
					dorp);
			if (0 <= ret) {
				return ret;
			}
		}
		if (declaration_name_get(dion)
		 && strcmp(declaration_name_get(dion), name) == 0) {
			*dorp = dion;
			if (scope->type == SCOPE_ENUM) {
				return TYPE_ENUM;
			} else {
				return dion->storage;
			}
		}
        }
}
