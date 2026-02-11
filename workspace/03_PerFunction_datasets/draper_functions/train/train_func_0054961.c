xmlrpc_wcs_to_utf8 (xmlrpc_env *env,
                                      wchar_t *wcs_data,
                                      size_t wcs_len)
{
    size_t estimate, bytes_used, i;
    xmlrpc_mem_block *output;
    unsigned char *buffer;
    wchar_t wc;
    int cwc;

    XMLRPC_ASSERT_ENV_OK(env);
    XMLRPC_ASSERT_PTR_OK(wcs_data);


    estimate = wcs_len * MAX_ENCODED_BYTES;
    output = XMLRPC_TYPED_MEM_BLOCK_NEW(char, env, estimate);
    XMLRPC_FAIL_IF_FAULT(env);


    buffer = (unsigned char*) XMLRPC_TYPED_MEM_BLOCK_CONTENTS(char, output);
    bytes_used = 0;
    for (i = 0; i < wcs_len; i++) {
        wc = wcs_data[i];
        cwc = wc;
        if (cwc <= 0x007F) {
            buffer[bytes_used++] = wc & 0x7F;
        } else if (cwc <= 0x07FF) {

            buffer[bytes_used++] = 0xC0 | (wc >> 6);
            buffer[bytes_used++] = 0x80 | (wc & 0x3F);
        } else if (cwc <= 0xFFFF) {

            buffer[bytes_used++] = 0xE0 | (wc >> 12);
            buffer[bytes_used++] = 0x80 | ((wc >> 6) & 0x3F);
            buffer[bytes_used++] = 0x80 | (wc & 0x3F);
        } else {
            XMLRPC_FAIL(env, XMLRPC_INTERNAL_ERROR,
                        "Don't know how to encode UCS-4 characters yet");
        }
    }


    XMLRPC_ASSERT(bytes_used <= estimate);


    XMLRPC_TYPED_MEM_BLOCK_RESIZE(char, env, output, bytes_used);
    XMLRPC_FAIL_IF_FAULT(env);

 cleanup:
    if (env->fault_occurred) {
        if (output)
            xmlrpc_mem_block_free(output);
        return NULL;
    }
    return output;
}
