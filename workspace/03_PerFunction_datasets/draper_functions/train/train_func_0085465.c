_dict_set (dict_t *this,
           char *key,
           data_t *value)
{
        int hashval;
        data_pair_t *pair;
        char key_free = 0;
        int tmp = 0;
        int ret = 0;

        if (!key) {
                ret = gf_asprintf (&key, "ref:%p", value);
                if (-1 == ret) {
                        gf_log ("dict", GF_LOG_WARNING, "asprintf failed %s", key);
                        return -1;
                }
                key_free = 1;
        }

        tmp = SuperFastHash (key, strlen (key));
        hashval = (tmp % this->hash_size);
        pair = _dict_lookup (this, key);

        if (pair) {
                data_t *unref_data = pair->value;
                pair->value = data_ref (value);
                data_unref (unref_data);
                if (key_free)
                        GF_FREE (key);

                return 0;
        }
        pair = (data_pair_t *) GF_CALLOC (1, sizeof (*pair),
                                          gf_common_mt_data_pair_t);
        if (!pair) {
                return -1;
        }

        pair->key = (char *) GF_CALLOC (1, strlen (key) + 1,
                                        gf_common_mt_char);
        if (!pair->key) {
                GF_FREE (pair);

                if (key_free)
                        GF_FREE (key);
                return -1;
        }

        strcpy (pair->key, key);
        pair->value = data_ref (value);

        pair->hash_next = this->members[hashval];
        this->members[hashval] = pair;

        pair->next = this->members_list;
        pair->prev = NULL;
        if (this->members_list)
                this->members_list->prev = pair;
        this->members_list = pair;
        this->count++;

        if (key_free)
                GF_FREE (key);
        return 0;
}
