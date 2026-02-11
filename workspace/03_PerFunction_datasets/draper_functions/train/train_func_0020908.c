zend_release_labels(TSRMLS_D)
{
	if (CG(labels)) {
		zend_hash_destroy(CG(labels));
		FREE_HASHTABLE(CG(labels));
	}
	if (!zend_stack_is_empty(&CG(labels_stack))) {
		HashTable **pht;

		zend_stack_top(&CG(labels_stack), (void**)&pht);
		CG(labels) = *pht;
		zend_stack_del_top(&CG(labels_stack));
	} else {
		CG(labels) = NULL;
	}
}
