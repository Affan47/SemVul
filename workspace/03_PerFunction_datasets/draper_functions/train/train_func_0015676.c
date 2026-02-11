get_one_challenge(void *arg, const char *key, k5_json_value val)
{
    struct get_one_challenge_data *data;
    unsigned long token_flags;
    int i;

    data = arg;
    if (data->err != 0)
        return;
    if (k5_json_get_tid(val) != K5_JSON_TID_NUMBER) {
        data->err = EINVAL;
        return;
    }

    token_flags = k5_json_number_value(val);

    for (i = 0; data->identities[i] != NULL; i++)
        continue;

    data->identities[i] = k5alloc(sizeof(*data->identities[i]), &data->err);
    if (data->identities[i] == NULL)
        return;
    data->identities[i]->identity = strdup(key);
    if (data->identities[i]->identity == NULL) {
        data->err = ENOMEM;
        return;
    }
    data->identities[i]->token_flags = token_flags;
}
