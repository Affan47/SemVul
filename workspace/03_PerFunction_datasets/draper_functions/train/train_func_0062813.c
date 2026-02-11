krb5_clear_error_message(krb5_context context)
{
    HEIMDAL_MUTEX_lock(context->mutex);
    if (context->error_string)
	free(context->error_string);
    context->error_code = 0;
    context->error_string = NULL;
    HEIMDAL_MUTEX_unlock(context->mutex);
}
