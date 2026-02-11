k5_arcfour_init_state (const krb5_keyblock *key,
                       krb5_keyusage keyusage, krb5_data *new_state)
{


    new_state->length = sizeof (ArcFourCipherState);
    new_state->data = malloc (new_state->length);
    if (new_state->data) {
        memset (new_state->data, 0 , new_state->length);

    }else {
        return (ENOMEM);
    }
    return 0;
}
