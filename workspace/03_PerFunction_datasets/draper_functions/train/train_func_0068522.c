spl_array_serialize(zval *object, unsigned char **buffer, zend_uint *buf_len, zend_serialize_data *data TSRMLS_DC)
{
	spl_array_object     *intern = (spl_array_object*)zend_object_store_get_object(object TSRMLS_CC);

	if (intern->fptr_serialize) {
		int retval;
		php_serialize_data_t *before;

		before = intern->serialize_data;
		intern->serialize_data = (php_serialize_data_t *)data;

		retval = zend_user_serialize(object, buffer, buf_len, data TSRMLS_CC);

		intern->serialize_data = before;

		return retval;
	} else {
		smart_str buf;

		buf = spl_array_serialize_helper(intern, (php_serialize_data_t *)data TSRMLS_CC);

		if (buf.c) {
			*buffer  = (unsigned char*)estrndup(buf.c, buf.len);
			*buf_len = buf.len;
			efree(buf.c);
			return SUCCESS;
		} else {
			return FAILURE;
		}
	}
}
