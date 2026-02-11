php_ob_init_named(uint initial_size, uint block_size, char *handler_name, zval *output_handler, uint chunk_size, zend_bool erase TSRMLS_DC)
{
	php_ob_buffer tmp_buf;

	if (output_handler && !zend_is_callable(output_handler, 0, NULL TSRMLS_CC)) {
		return FAILURE;
	}

	tmp_buf.block_size = block_size;
	tmp_buf.size = initial_size;
	tmp_buf.buffer = (char *) emalloc(initial_size+1);
	tmp_buf.text_length = 0;
	tmp_buf.output_handler = output_handler;
	tmp_buf.chunk_size = chunk_size;
	tmp_buf.status = 0;
	tmp_buf.internal_output_handler = NULL;
	tmp_buf.internal_output_handler_buffer = NULL;
	tmp_buf.internal_output_handler_buffer_size = 0;
	tmp_buf.handler_name = estrdup(handler_name&&handler_name[0]?handler_name:OB_DEFAULT_HANDLER_NAME);
	tmp_buf.erase = erase;

	if (OG(ob_nesting_level)>0) {
#if HAVE_ZLIB && !defined(COMPILE_DL_ZLIB)
		if (!strncmp(handler_name, "ob_gzhandler", sizeof("ob_gzhandler")) && php_ob_gzhandler_check(TSRMLS_C)) {
			return FAILURE;
		}
#endif
		if (OG(ob_nesting_level)==1) {
			zend_stack_init(&OG(ob_buffers));
		}
		zend_stack_push(&OG(ob_buffers), &OG(active_ob_buffer), sizeof(php_ob_buffer));
	}
	OG(ob_nesting_level)++;
	OG(active_ob_buffer) = tmp_buf;
	OG(php_body_write) = php_b_body_write;
	return SUCCESS;
}
