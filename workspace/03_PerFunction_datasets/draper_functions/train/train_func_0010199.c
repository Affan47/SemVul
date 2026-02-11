get_subjectaltnames(X509 *x509, unsigned int *count)
{
    unsigned int            local_count;
    unsigned char           **result;
    STACK_OF(GENERAL_NAME)  *san_stack = (STACK_OF(GENERAL_NAME)*)X509_get_ext_d2i(x509, NID_subject_alt_name, NULL, NULL);
    unsigned char           *temp[sk_GENERAL_NAME_num(san_stack)];
    GENERAL_NAME            *name;
    int                     i;

    local_count = 0;
    result = NULL;
    name = NULL;
    *count = 0;
    while(sk_GENERAL_NAME_num(san_stack) > 0) {
        name = sk_GENERAL_NAME_pop(san_stack);
        switch(name->type) {
            case GEN_DNS:
                temp[local_count] = strndup(ASN1_STRING_data(name->d.dNSName), ASN1_STRING_length(name->d.dNSName)
                                    + 1);
                if(temp[local_count] == NULL)
                    conf_err("out of memory");
                local_count++;
                break;
            default:
              logmsg(LOG_INFO, "unsupported subjectAltName type encountered: %i", name->type);
        }
        GENERAL_NAME_free(name);
    }

    result = (unsigned char**)malloc(sizeof(unsigned char*)*local_count);
    if(result == NULL)
        conf_err("out of memory");
    for(i = 0;i < local_count; i++) {
        result[i] = strndup(temp[i], strlen(temp[i])+1);
        if(result[i] == NULL)
            conf_err("out of memory");
        free(temp[i]);
    }
    *count = local_count;

    sk_GENERAL_NAME_pop_free(san_stack, GENERAL_NAME_free);

    return result;
}
