pki_do_sign(const ssh_key privkey,
                          const unsigned char *hash,
                          size_t hlen) {
    ssh_signature sig;

    sig = ssh_signature_new();
    if (sig == NULL) {
        return NULL;
    }

    sig->type = privkey->type;

    switch(privkey->type) {
        case SSH_KEYTYPE_DSS:
            sig->dsa_sig = DSA_do_sign(hash, hlen, privkey->dsa);
            if (sig->dsa_sig == NULL) {
                ssh_signature_free(sig);
                return NULL;
            }

#ifdef DEBUG_CRYPTO
            ssh_print_bignum("r", sig->dsa_sig->r);
            ssh_print_bignum("s", sig->dsa_sig->s);
#endif

            break;
        case SSH_KEYTYPE_RSA:
        case SSH_KEYTYPE_RSA1:
            sig->rsa_sig = _RSA_do_sign(hash, hlen, privkey->rsa);
            if (sig->rsa_sig == NULL) {
                ssh_signature_free(sig);
                return NULL;
            }
            sig->dsa_sig = NULL;
            break;
        case SSH_KEYTYPE_ECDSA:
#ifdef HAVE_OPENSSL_ECC
            sig->ecdsa_sig = ECDSA_do_sign(hash, hlen, privkey->ecdsa);
            if (sig->ecdsa_sig == NULL) {
                ssh_signature_free(sig);
                return NULL;
            }

# ifdef DEBUG_CRYPTO
            ssh_print_bignum("r", sig->ecdsa_sig->r);
            ssh_print_bignum("s", sig->ecdsa_sig->s);
# endif

            break;
#endif
        case SSH_KEYTYPE_UNKNOWN:
            ssh_signature_free(sig);
            return NULL;
    }

    return sig;
}
