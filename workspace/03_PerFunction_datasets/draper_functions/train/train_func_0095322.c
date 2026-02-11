ktest_empty_authenticator(krb5_authenticator *a)
{
    if (a->client)
        ktest_destroy_principal(&a->client);
    if (a->checksum)
        ktest_destroy_checksum(&a->checksum);
    if (a->subkey)
        ktest_destroy_keyblock(&a->subkey);
    if (a->authorization_data)
        ktest_destroy_authorization_data(&a->authorization_data);
}
