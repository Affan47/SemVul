pki_signature_verify(ssh_session session,
                         const ssh_signature sig,
                         const ssh_key key,
                         const unsigned char *hash,
                         size_t hlen)
{
    int rc;

    switch(key->type) {
        case SSH_KEYTYPE_DSS:
            rc = DSA_do_verify(hash,
                               hlen,
                               sig->dsa_sig,
                               key->dsa);
            if (rc <= 0) {
                ssh_set_error(session,
                              SSH_FATAL,
                              "DSA error: %s",
                              ERR_error_string(ERR_get_error(), NULL));
                return SSH_ERROR;
            }
            break;
        case SSH_KEYTYPE_RSA:
        case SSH_KEYTYPE_RSA1:
            rc = RSA_verify(NID_sha1,
                            hash,
                            hlen,
                            ssh_string_data(sig->rsa_sig),
                            ssh_string_len(sig->rsa_sig),
                            key->rsa);
            if (rc <= 0) {
                ssh_set_error(session,
                              SSH_FATAL,
                              "RSA error: %s",
                              ERR_error_string(ERR_get_error(), NULL));
                return SSH_ERROR;
            }
            break;
        case SSH_KEYTYPE_ECDSA:
#ifdef HAVE_OPENSSL_ECC
            rc = ECDSA_do_verify(hash,
                                 hlen,
                                 sig->ecdsa_sig,
                                 key->ecdsa);
            if (rc <= 0) {
                ssh_set_error(session,
                              SSH_FATAL,
                              "ECDSA error: %s",
                              ERR_error_string(ERR_get_error(), NULL));
                return SSH_ERROR;
            }
            break;
#endif
        case SSH_KEYTYPE_UNKNOWN:
            ssh_set_error(session, SSH_FATAL, "Unknown public key type");
            return SSH_ERROR;
    }

    return SSH_OK;
}
