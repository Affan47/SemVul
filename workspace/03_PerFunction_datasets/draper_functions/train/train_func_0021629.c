krb5_responder_get_challenge(krb5_context ctx, krb5_responder_context rctx,
                             const char *question)
{
    if (rctx == NULL)
        return NULL;

    return k5_response_items_get_challenge(rctx->items, question);
}
