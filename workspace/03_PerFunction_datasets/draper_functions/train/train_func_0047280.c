php_ob_append(const char *text, uint text_length TSRMLS_DC)
{
	char *target;
	uint original_ob_text_length;

	original_ob_text_length=OG(active_ob_buffer).text_length;

	php_ob_allocate(text_length TSRMLS_CC);
	target = OG(active_ob_buffer).buffer+original_ob_text_length;
	memcpy(target, text, text_length);
	target[text_length]=0;


	if (OG(active_ob_buffer).chunk_size
		&& OG(active_ob_buffer).text_length >= OG(active_ob_buffer).chunk_size) {

		php_end_ob_buffer(1, 1 TSRMLS_CC);
		return;
	}
}
