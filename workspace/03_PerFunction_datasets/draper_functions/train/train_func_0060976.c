ssh_pki_export_signature_blob(const ssh_signature sig,
                                  ssh_string *sig_blob)
{
    ssh_buffer buf = NULL;
    ssh_string str;
    int rc;

    if (sig == NULL || sig_blob == NULL) {
        return SSH_ERROR;
    }

    buf = ssh_buffer_new();
    if (buf == NULL) {
        return SSH_ERROR;
    }

    str = ssh_string_from_char(sig->type_c);
    if (str == NULL) {
        ssh_buffer_free(buf);
        return SSH_ERROR;
    }

    rc = buffer_add_ssh_string(buf, str);
    ssh_string_free(str);
    if (rc < 0) {
        ssh_buffer_free(buf);
        return SSH_ERROR;
    }

    str = pki_signature_to_blob(sig);
    if (str == NULL) {
        ssh_buffer_free(buf);
        return SSH_ERROR;
    }

    rc = buffer_add_ssh_string(buf, str);
    ssh_string_free(str);
    if (rc < 0) {
        ssh_buffer_free(buf);
        return SSH_ERROR;
    }

    str = ssh_string_new(buffer_get_rest_len(buf));
    if (str == NULL) {
        ssh_buffer_free(buf);
        return SSH_ERROR;
    }

    ssh_string_fill(str, buffer_get_rest(buf), buffer_get_rest_len(buf));
    ssh_buffer_free(buf);

    *sig_blob = str;

    return SSH_OK;
}
