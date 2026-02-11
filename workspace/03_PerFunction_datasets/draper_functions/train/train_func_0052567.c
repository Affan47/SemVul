php_output_context_swap(php_output_context *context)
{
	if (context->in.free && context->in.data) {
		efree(context->in.data);
	}
	context->in.data = context->out.data;
	context->in.used = context->out.used;
	context->in.free = context->out.free;
	context->in.size = context->out.size;
	context->out.data = NULL;
	context->out.used = 0;
	context->out.free = 0;
	context->out.size = 0;
}
