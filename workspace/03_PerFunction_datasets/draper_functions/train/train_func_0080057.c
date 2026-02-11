checkNameTy(Absyn * node, Table * symtab)
{
	Entry *entry;
	entry = lookup(symtab, node->u.nameTy.name);
	if (entry == NULL) {
		error("undefined type '%s' in line %d",
		      symToString(node->u.nameTy.name), node->line);
	}

	if (entry->kind != ENTRY_KIND_TYPE)
		error("'%s' is not a type in line %d",
		      symToString(node->u.nameTy.name), node->line);

	return entry->u.typeEntry.type;
}
