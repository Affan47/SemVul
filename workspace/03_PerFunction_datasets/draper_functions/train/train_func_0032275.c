krb5int_des_init_state(const krb5_keyblock *key, krb5_keyusage usage,
                       krb5_data *new_state)
{
    new_state->length = 8;
    new_state->data = (void *) malloc(8);
    if (new_state->data) {
        memset (new_state->data, 0, new_state->length);

        if (key->enctype == ENCTYPE_DES_CBC_CRC) {
            memcpy (new_state->data, key->contents, new_state->length);
        }
    } else {
        return ENOMEM;
    }
    return 0;
}
