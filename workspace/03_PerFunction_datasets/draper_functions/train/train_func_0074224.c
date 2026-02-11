spl_caching_it_rewind(spl_dual_it_object *intern TSRMLS_DC)
{
	spl_dual_it_rewind(intern TSRMLS_CC);
	zend_hash_clean(HASH_OF(intern->u.caching.zcache));
	spl_caching_it_next(intern TSRMLS_CC);
}
