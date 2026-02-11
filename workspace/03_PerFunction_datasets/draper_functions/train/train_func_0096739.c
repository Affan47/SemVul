declaration_rename_structunionenum(
	struct declaration *dion,
	enum type_type type,
	const char *old,
	const char *new
)
{
	struct expr *initializer;

	type_rename_structunionenum(dion->type_name, type, old, new);

	initializer = declaration_initializer_get(dion);
	if (initializer) {
		expr_rename_structunionenum(initializer, type, old, new);
	}
}
