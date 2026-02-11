file_next_line(dns_file_handle_t *handle)
{
    char *p, *lnext_org;
    int len;

redo:
    lnext_org = handle->fh_lnext;

    p = handle->fh_lnext;
    len = handle->fh_len;

    if (p != NULL) {
        handle->fh_line++;

        for (; len > 0; p++, len--) {
            if (*p == '\n') {
                *p = 0;
                handle->fh_len = len - 1;
                handle->fh_lnext = p + 1;
                handle->fh_curp = lnext_org;
                file_ignore_comment(lnext_org);
                return 0;
            }
        }

        memcpy(handle->fh_buf, handle->fh_lnext, handle->fh_len);
    }

    if (file_read_buf(handle, handle->fh_len) <= 0)
        return -1;

    goto redo;
}
