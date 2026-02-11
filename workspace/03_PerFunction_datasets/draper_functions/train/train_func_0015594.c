hash_add_item(ht, hi, key, hash)
    hashtab_T	*ht;
    hashitem_T	*hi;
    char_u	*key;
    hash_T	hash;
{

    if (ht->ht_error && hash_may_resize(ht, 0) == FAIL)
	return FAIL;

    ++ht->ht_used;
    if (hi->hi_key == NULL)
	++ht->ht_filled;
    hi->hi_key = key;
    hi->hi_hash = hash;


    return hash_may_resize(ht, 0);
}
