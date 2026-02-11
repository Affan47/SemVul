zend_rsrc_list_get_rsrc_type(int resource TSRMLS_DC)
{
	zend_rsrc_list_dtors_entry *lde;
	int rsrc_type;

	if (!zend_list_find(resource, &rsrc_type))
		return NULL;

	if (zend_hash_index_find(&list_destructors, rsrc_type, (void **) &lde)==SUCCESS) {
		return lde->type_name;
	} else {
		return NULL;
	}
}
