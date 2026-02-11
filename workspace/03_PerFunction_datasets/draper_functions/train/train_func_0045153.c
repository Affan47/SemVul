krb5_crypto_destroy(krb5_context context,
		    krb5_crypto crypto)
{
    int i;

    for(i = 0; i < crypto->num_key_usage; i++)
	free_key_usage(context, &crypto->key_usage[i], crypto->et);
    free(crypto->key_usage);
    _krb5_free_key_data(context, &crypto->key, crypto->et);
    free (crypto);
    return 0;
}
