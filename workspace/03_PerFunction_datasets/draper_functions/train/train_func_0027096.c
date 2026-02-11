_zend_list_find(int id, int *type TSRMLS_DC)
{
	zend_rsrc_list_entry *le;

	if (zend_hash_index_find(&EG(regular_list), id, (void **) &le)==SUCCESS) {
		*type = le->type;
		return le->ptr;
	} else {
		*type = -1;
		return NULL;
	}
}
