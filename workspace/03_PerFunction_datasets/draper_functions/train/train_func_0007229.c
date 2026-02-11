spl_object_storage_attach(spl_SplObjectStorage *intern, zval *obj, zval *inf TSRMLS_DC)
{
	spl_SplObjectStorageElement *pelement, element;
	pelement = spl_object_storage_get(intern, obj TSRMLS_CC);
	if (inf) {
		Z_ADDREF_P(inf);
	} else {
		ALLOC_INIT_ZVAL(inf);
	}
	if (pelement) {
		zval_ptr_dtor(&pelement->inf);
		pelement->inf = inf;
		return;
	}
	Z_ADDREF_P(obj);
	element.obj = obj;
	element.inf = inf;
#if HAVE_PACKED_OBJECT_VALUE
	zend_hash_update(&intern->storage, (char*)&Z_OBJVAL_P(obj), sizeof(zend_object_value), &element, sizeof(spl_SplObjectStorageElement), NULL);
#else
	{
		zend_object_value zvalue;
		memset(&zvalue, 0, sizeof(zend_object_value));
		zvalue.handle = Z_OBJ_HANDLE_P(obj);
		zvalue.handlers = Z_OBJ_HT_P(obj);
		zend_hash_update(&intern->storage, (char*)&zvalue, sizeof(zend_object_value), &element, sizeof(spl_SplObjectStorageElement), NULL);
	}
#endif
}
