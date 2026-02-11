globus_l_remove_proxy(
    gss_buffer_t                        token)
{
    char * p;
    char * q;
    size_t len;

    q = memchr(token->value, '=', token->length);
    if (q == NULL)
    {
        return;
    }

    len = token->length - (q - (char *) token->value);

    p = malloc(len);
    if (p == NULL)
    {
        return;
    }
    memcpy(p, q+1, len-1);
    p[len-1] = 0;

    (void) remove(p);
    free(p);
}
