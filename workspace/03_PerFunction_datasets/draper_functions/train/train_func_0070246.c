webauth_keyring_decode(struct webauth_context *ctx, const char *input,
                       size_t length, struct webauth_keyring **output)
{
    size_t i;
    int s;
    struct webauth_keyring *ring;
    struct wai_keyring data;


    *output = NULL;
    memset(&data, 0, sizeof(data));
    s = wai_decode(ctx, wai_keyring_encoding, input, length, &data);
    if (s != WA_ERR_NONE)
        return s;
    if (data.version != KEYRING_VERSION) {
        s = WA_ERR_FILE_VERSION;
        wai_error_set(ctx, s, "unsupported keyring data version %d",
                      data.version);
        return s;
    }


    ring = webauth_keyring_new(ctx, data.entry_count);
    for (i = 0; i < data.entry_count; i++) {
        struct wai_keyring_entry *entry;
        struct webauth_key *key;

        entry = &data.entry[i];
        s = webauth_key_create(ctx, entry->key_type, entry->key_len,
                               entry->key, &key);
        if (s != WA_ERR_NONE)
            return s;
        webauth_keyring_add(ctx, ring, entry->creation, entry->valid_after,
                            key);
    }
    *output = ring;
    return WA_ERR_NONE;
}
