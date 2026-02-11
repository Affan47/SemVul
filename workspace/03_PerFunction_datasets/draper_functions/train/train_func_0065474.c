zend_register_constant(zend_constant *c TSRMLS_DC)
{
	char *lowercase_name = NULL;
	char *name;
	int ret = SUCCESS;

#if 0
	printf("Registering constant for module %d\n", c->module_number);
#endif

	if (!(c->flags & CONST_CS)) {

		lowercase_name = estrndup(c->name, c->name_len-1);
		zend_str_tolower(lowercase_name, c->name_len-1);
		name = lowercase_name;
	} else {
		char *slash = strrchr(c->name, '\\');
		if(slash) {
			lowercase_name = estrndup(c->name, c->name_len-1);
			zend_str_tolower(lowercase_name, slash-c->name);
			name = lowercase_name;
		} else {
			name = c->name;
		}
	}


	if ((c->name_len == sizeof("__COMPILER_HALT_OFFSET__")
		&& !memcmp(name, "__COMPILER_HALT_OFFSET__", sizeof("__COMPILER_HALT_OFFSET__")-1))
		|| zend_hash_add(EG(zend_constants), name, c->name_len, (void *) c, sizeof(zend_constant), NULL)==FAILURE) {


		if (c->name[0] == '\0' && c->name_len > sizeof("\0__COMPILER_HALT_OFFSET__")
			&& memcmp(name, "\0__COMPILER_HALT_OFFSET__", sizeof("\0__COMPILER_HALT_OFFSET__")) == 0) {
			name++;
		}
		zend_error(E_NOTICE,"Constant %s already defined", name);
		free(c->name);
		if (!(c->flags & CONST_PERSISTENT)) {
			zval_dtor(&c->value);
		}
		ret = FAILURE;
	}
	if (lowercase_name) {
		efree(lowercase_name);
	}
	return ret;
}
