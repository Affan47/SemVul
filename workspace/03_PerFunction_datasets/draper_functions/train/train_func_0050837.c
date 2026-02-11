ossl_x509name_hash_old(VALUE self)
{
    X509_NAME *name;
    unsigned long hash;

    GetX509Name(self, name);

    hash = X509_NAME_hash_old(name);

    return ULONG2NUM(hash);
}
