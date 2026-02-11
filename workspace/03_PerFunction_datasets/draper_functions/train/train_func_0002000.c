free_private_key(struct private_key *key)
{
    free_AlgorithmIdentifier(&key->alg);
    if (key->private_key)
	hx509_private_key_free(&key->private_key);
    der_free_octet_string(&key->localKeyId);
    free(key);
}
