zend_ini_string_ex(char *name, uint name_length, int orig, zend_bool *exists)
{
	zend_ini_entry *ini_entry;
	TSRMLS_FETCH();

	if (zend_hash_find(EG(ini_directives), name, name_length, (void **) &ini_entry) == SUCCESS) {
		if (exists) {
			*exists = 1;
		}

		if (orig && ini_entry->modified) {
			return ini_entry->orig_value;
		} else {
			return ini_entry->value;
		}
	} else {
		if (exists) {
			*exists = 0;
		}
		return NULL;
	}
}
