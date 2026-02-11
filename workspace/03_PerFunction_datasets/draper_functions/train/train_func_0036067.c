ossl_x509store_add_cert(VALUE self, VALUE arg)
{
    X509_STORE *store;
    X509 *cert;

    cert = GetX509CertPtr(arg);
    GetX509Store(self, store);
    if (X509_STORE_add_cert(store, cert) != 1){
        ossl_raise(eX509StoreError, NULL);
    }

    return self;
}
