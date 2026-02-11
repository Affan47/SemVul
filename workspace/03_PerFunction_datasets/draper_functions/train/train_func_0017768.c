ssh_message_auth_reply_pk_ok_simple(ssh_message msg) {
    ssh_string algo;
    ssh_string pubkey_blob = NULL;
    int ret;

    algo = ssh_string_from_char(msg->auth_request.pubkey->type_c);
    if (algo == NULL) {
        return SSH_ERROR;
    }

    ret = ssh_pki_export_pubkey_blob(msg->auth_request.pubkey, &pubkey_blob);
    if (ret < 0) {
        ssh_string_free(algo);
        return SSH_ERROR;
    }

    ret = ssh_message_auth_reply_pk_ok(msg, algo, pubkey_blob);

    ssh_string_free(algo);
    ssh_string_free(pubkey_blob);

    return ret;
}
