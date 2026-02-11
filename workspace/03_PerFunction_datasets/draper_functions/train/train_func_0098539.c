test_hash_int(tst_case *tc, void *data)
{
    int i;
    HashTable *ht = h_new_int(&free);
    char buf[100];
    char *word;
    (void)data;

    Aiequal(0, ht->size);
    Aiequal(HASH_KEY_DOES_NOT_EXIST, h_set_int(ht, 0, estrdup("one")));
    Aiequal(1, ht->size);
    Atrue(h_has_key_int(ht, 0));
    h_set_int(ht, 10, estrdup("ten"));
    Aiequal(2, ht->size);
    Atrue(h_has_key_int(ht, 10));
    h_set_int(ht, 1000, estrdup("thousand"));
    Aiequal(3, ht->size);
    Atrue(h_has_key_int(ht, 1000));
    Asequal("thousand", word = h_rem_int(ht, 1000));
    Aiequal(2, ht->size);
    Atrue(!h_has_key_int(ht, 1000));
    Atrue(h_has_key_int(ht, 10));
    Atrue(!h_set_safe_int(ht, 10, word));
    free(word);
    h_del_int(ht, 10);

    for (i = 0; i < HASH_INT_TEST_SIZE; i++) {
        sprintf(buf, "<%d>", i);
        h_set_int(ht, i, estrdup(buf));
    }
    Asequal("<0>", h_get_int(ht, 0));
    Asequal("<100>", h_get_int(ht, 100));
    for (i = 0; i < HASH_INT_TEST_SIZE; i++) {
        sprintf(buf, "<%d>", i);
        Asequal(buf, h_get_int(ht, i));
    }

    for (i = 0; i < HASH_INT_TEST_SIZE; i++) {
        h_del_int(ht, i);
    }
    Aiequal(0, ht->size);

    h_destroy(ht);
}
