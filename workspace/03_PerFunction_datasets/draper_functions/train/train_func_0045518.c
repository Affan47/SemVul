SSL_CTX_load_verify_locations(SSL_CTX* ctx, const char* file,
                                  const char* path)
{
    CYASSL_ENTER("SSL_CTX_load_verify_locations");
    (void)path;

    if (ctx == NULL || file == NULL)
        return SSL_FAILURE;

    if (ProcessFile(ctx, file, SSL_FILETYPE_PEM, CA_TYPE,NULL,0) == SSL_SUCCESS)
        return SSL_SUCCESS;

    return SSL_FAILURE;
}
