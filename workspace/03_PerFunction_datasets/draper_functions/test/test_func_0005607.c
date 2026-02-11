convert_scalar_to_array(zval *op, int type TSRMLS_DC)
{
	zval *entry;

	ALLOC_ZVAL(entry);
	*entry = *op;
	INIT_PZVAL(entry);

	switch (type) {
		case IS_ARRAY:
			ALLOC_HASHTABLE(Z_ARRVAL_P(op));
			zend_hash_init(Z_ARRVAL_P(op), 0, NULL, ZVAL_PTR_DTOR, 0);
			zend_hash_index_update(Z_ARRVAL_P(op), 0, (void *) &entry, sizeof(zval *), NULL);
			Z_TYPE_P(op) = IS_ARRAY;
			break;
		case IS_OBJECT:
			object_init(op);
			zend_hash_update(Z_OBJPROP_P(op), "scalar", sizeof("scalar"), (void *) &entry, sizeof(zval *), NULL);
			break;
	}
}
