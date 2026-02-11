__gf_calloc (size_t nmemb, size_t size, uint32_t type)
{
        size_t          tot_size = 0;
        size_t          req_size = 0;
        char            *ptr = NULL;
        xlator_t        *xl = NULL;

        if (!THIS->ctx->mem_acct_enable)
                return CALLOC (nmemb, size);

        xl = THIS;

        req_size = nmemb * size;
        tot_size = req_size + GF_MEM_HEADER_SIZE + GF_MEM_TRAILER_SIZE;

        ptr = calloc (1, tot_size);

        if (!ptr) {
                gf_log_nomem ("", GF_LOG_ALERT, tot_size);
                return NULL;
        }
        gf_mem_set_acct_info (xl, &ptr, req_size, type);

        return (void *)ptr;
}
