ifName_get(ifXTable_rowreq_ctx * rowreq_ctx, char **ifName_val_ptr_ptr,
           size_t * ifName_val_ptr_len_ptr)
{
    size_t tmp_len;


    netsnmp_assert((NULL != ifName_val_ptr_ptr)
                   && (NULL != *ifName_val_ptr_ptr));
    netsnmp_assert(NULL != ifName_val_ptr_len_ptr);


    DEBUGMSGTL(("verbose:ifXTable:ifName_get", "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);


    tmp_len = strlen(rowreq_ctx->data.ifName);
    if ((NULL == (*ifName_val_ptr_ptr)) ||
        ((*ifName_val_ptr_len_ptr) < tmp_len)) {


        (*ifName_val_ptr_ptr) = (char*)malloc(tmp_len);
        if (NULL == (*ifName_val_ptr_ptr)) {
            snmp_log(LOG_ERR, "could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (*ifName_val_ptr_len_ptr) = tmp_len;
    memcpy((*ifName_val_ptr_ptr), rowreq_ctx->data.ifName, tmp_len);

    return MFD_SUCCESS;
}
