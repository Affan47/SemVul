php_output_stack_apply_op(void *h, void *c)
{
	int was_disabled;
	php_output_handler_status_t status;
	php_output_handler *handler = *(php_output_handler **) h;
	php_output_context *context = (php_output_context *) c;

	if ((was_disabled = (handler->flags & PHP_OUTPUT_HANDLER_DISABLED))) {
		status = PHP_OUTPUT_HANDLER_FAILURE;
	} else {
		status = php_output_handler_op(handler, context);
	}


	switch (status) {
		case PHP_OUTPUT_HANDLER_NO_DATA:
			return 1;

		case PHP_OUTPUT_HANDLER_SUCCESS:

			if (handler->level) {
				php_output_context_swap(context);
			}
			return 0;

		case PHP_OUTPUT_HANDLER_FAILURE:
		default:
			if (was_disabled) {

				if (!handler->level) {
					php_output_context_pass(context);
				}
			} else {

				if (handler->level) {
					php_output_context_swap(context);
				}
			}
			return 0;
	}
}
