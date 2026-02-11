_php_stream_alloc(php_stream_ops *ops, void *abstract, const char *persistent_id, const char *mode STREAMS_DC TSRMLS_DC)
{
	php_stream *ret;

	ret = (php_stream*) pemalloc_rel_orig(sizeof(php_stream), persistent_id ? 1 : 0);

	memset(ret, 0, sizeof(php_stream));

	ret->readfilters.stream = ret;
	ret->writefilters.stream = ret;

#if STREAM_DEBUG
fprintf(stderr, "stream_alloc: %s:%p persistent=%s\n", ops->label, ret, persistent_id);
#endif

	ret->ops = ops;
	ret->abstract = abstract;
	ret->is_persistent = persistent_id ? 1 : 0;
	ret->chunk_size = FG(def_chunk_size);

#if ZEND_DEBUG
	ret->open_filename = __zend_orig_filename ? __zend_orig_filename : __zend_filename;
	ret->open_lineno = __zend_orig_lineno ? __zend_orig_lineno : __zend_lineno;
#endif

	if (FG(auto_detect_line_endings)) {
		ret->flags |= PHP_STREAM_FLAG_DETECT_EOL;
	}

	if (persistent_id) {
		zend_rsrc_list_entry le;

		Z_TYPE(le) = le_pstream;
		le.ptr = ret;
		le.refcount = 0;

		if (FAILURE == zend_hash_update(&EG(persistent_list), (char *)persistent_id,
					strlen(persistent_id) + 1,
					(void *)&le, sizeof(le), NULL)) {

			pefree(ret, 1);
			return NULL;
		}
	}

	ret->rsrc_id = ZEND_REGISTER_RESOURCE(NULL, ret, persistent_id ? le_pstream : le_stream);
	strlcpy(ret->mode, mode, sizeof(ret->mode));

	return ret;
}
