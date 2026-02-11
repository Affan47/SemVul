krb5_free_context(krb5_context context)
{
    krb5_clear_error_message(context);

    HEIMDAL_MUTEX_destroy(context->mutex);
    free(context->mutex);
    if (context->flags & KRB5_CTX_F_SOCKETS_INITIALIZED) {
        rk_SOCK_EXIT();
    }

    memset(context, 0, sizeof(*context));
    free(context);
}
