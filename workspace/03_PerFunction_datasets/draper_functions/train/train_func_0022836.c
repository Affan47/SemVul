krb5int_fast_free_state(krb5_context context,
                        struct krb5int_fast_request_state *state)
{
    if (state == NULL)
        return;

    krb5_free_keyblock(context, state->armor_key);
    krb5_free_fast_armor(context, state->armor);
    free(state);
}
