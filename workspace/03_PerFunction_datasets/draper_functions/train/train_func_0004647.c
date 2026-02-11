memdup(u_char ** to, const void * from, size_t size)
{
    if (to == NULL)
        return SNMPERR_GENERR;
    if (from == NULL) {
        *to = NULL;
        return SNMPERR_SUCCESS;
    }
    if ((*to = (u_char *) malloc(size)) == NULL)
        return SNMPERR_GENERR;
    memcpy(*to, from, size);
    return SNMPERR_SUCCESS;

}
