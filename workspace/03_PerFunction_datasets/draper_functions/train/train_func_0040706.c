ssh_pki_export_pubkey_blob(const ssh_key key,
                               ssh_string *pblob)
{
    ssh_string blob;

    if (key == NULL) {
        return SSH_OK;
    }

    blob = pki_publickey_to_blob(key);
    if (blob == NULL) {
        return SSH_ERROR;
    }

    *pblob = blob;
    return SSH_OK;
}
