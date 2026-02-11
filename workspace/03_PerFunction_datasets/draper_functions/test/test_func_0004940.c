spl_dual_it_free(spl_dual_it_object *intern TSRMLS_DC)
{
	if (intern->inner.iterator && intern->inner.iterator->funcs->invalidate_current) {
		intern->inner.iterator->funcs->invalidate_current(intern->inner.iterator TSRMLS_CC);
	}
	if (intern->current.data) {
		zval_ptr_dtor(&intern->current.data);
		intern->current.data = NULL;
	}
	if (intern->current.str_key) {
		efree(intern->current.str_key);
		intern->current.str_key = NULL;
	}
	if (intern->dit_type == DIT_CachingIterator || intern->dit_type == DIT_RecursiveCachingIterator) {
		if (intern->u.caching.zstr) {
			zval_ptr_dtor(&intern->u.caching.zstr);
			intern->u.caching.zstr = NULL;
		}
		if (intern->u.caching.zchildren) {
			zval_ptr_dtor(&intern->u.caching.zchildren);
			intern->u.caching.zchildren = NULL;
		}
	}
}
