list_entry_destructor(void *ptr)
{
	zend_rsrc_list_entry *le = (zend_rsrc_list_entry *) ptr;
	zend_rsrc_list_dtors_entry *ld;
	TSRMLS_FETCH();

	if (zend_hash_index_find(&list_destructors, le->type, (void **) &ld)==SUCCESS) {
		switch (ld->type) {
			case ZEND_RESOURCE_LIST_TYPE_STD:
				if (ld->list_dtor) {
					(ld->list_dtor)(le->ptr);
				}
				break;
			case ZEND_RESOURCE_LIST_TYPE_EX:
				if (ld->list_dtor_ex) {
					ld->list_dtor_ex(le TSRMLS_CC);
				}
				break;
			EMPTY_SWITCH_DEFAULT_CASE()
		}
	} else {
		zend_error(E_WARNING,"Unknown list entry type in request shutdown (%d)", le->type);
	}
}
