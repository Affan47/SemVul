_extension_class_string(zend_class_entry **pce TSRMLS_DC, int num_args, va_list args, zend_hash_key *hash_key)
{
	string *str = va_arg(args, string *);
	char *indent = va_arg(args, char *);
	struct _zend_module_entry *module = va_arg(args, struct _zend_module_entry*);
	int *num_classes = va_arg(args, int*);

	if ((*pce)->module && !strcasecmp((*pce)->module->name, module->name)) {
		string_printf(str, "\n");
		_class_string(str, *pce, NULL, indent TSRMLS_CC);
		(*num_classes)++;
	}
	return ZEND_HASH_APPLY_KEEP;
}
