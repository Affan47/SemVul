krb5_authenticator_size(krb5_context kcontext, krb5_pointer arg, size_t *sizep)
{
    krb5_error_code     kret;
    krb5_authenticator  *authenticator;
    size_t              required;


    kret = EINVAL;
    if ((authenticator = (krb5_authenticator *) arg)) {
        required = sizeof(krb5_int32)*6;


        if (authenticator->client)
            kret = krb5_size_opaque(kcontext,
                                    KV5M_PRINCIPAL,
                                    (krb5_pointer) authenticator->client,
                                    &required);
        else
            kret = 0;


        if (!kret && authenticator->checksum)
            kret = krb5_size_opaque(kcontext,
                                    KV5M_CHECKSUM,
                                    (krb5_pointer) authenticator->checksum,
                                    &required);


        if (!kret && authenticator->subkey)
            kret = krb5_size_opaque(kcontext,
                                    KV5M_KEYBLOCK,
                                    (krb5_pointer) authenticator->subkey,
                                    &required);


        if (!kret && authenticator->authorization_data) {
            int i;

            for (i=0; !kret && authenticator->authorization_data[i]; i++) {
                kret = krb5_size_opaque(kcontext,
                                        KV5M_AUTHDATA,
                                        (krb5_pointer) authenticator->
                                        authorization_data[i],
                                        &required);
            }
        }
    }
    if (!kret)
        *sizep += required;
    return(kret);
}
