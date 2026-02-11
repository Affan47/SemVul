kmGLClearContext(km_mat4_stack_context *context)
{

    if (context->entry->prev)
        context->entry->prev->next = context->entry->next;


	km_mat4_stack_release(&context->modelview_matrix_stack);
	km_mat4_stack_release(&context->projection_matrix_stack);
	km_mat4_stack_release(&context->texture_matrix_stack);


	context->initialized = 0;


	context->current_stack = NULL;


    free(context->entry);
}
