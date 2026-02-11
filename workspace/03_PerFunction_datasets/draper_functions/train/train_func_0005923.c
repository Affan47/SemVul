declare_symbol(uint32_t symbol_type, hashtab_key_t key, hashtab_datum_t datum, uint32_t * dest_value, uint32_t * datum_value)
{
	avrule_decl_t *decl = stack_top->decl;
	int retval;


	if (!is_declaration_allowed()) {
		return -1;
	}
	retval = symtab_insert(policydbp, symbol_type, key, datum, SCOPE_DECL, decl->decl_id, dest_value);
	if (retval == 1 && dest_value) {
		symtab_datum_t *s = (symtab_datum_t *) hashtab_search(policydbp->symtab[symbol_type].table,
								      key);
		assert(s != NULL);

		if (symbol_type == SYM_LEVELS) {
			*dest_value = ((level_datum_t *) s)->level->sens;
		} else {
			*dest_value = s->value;
		}
	} else if (retval == -2) {
		return -2;
	} else if (retval < 0) {
		return -3;
	} else {
	}
	if (datum_value != NULL) {
		if (ebitmap_set_bit(decl->declared.scope + symbol_type, *datum_value - 1, 1)) {
			return -3;
		}
	}
	return retval;
}
