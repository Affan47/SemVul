yajl_alloc(const yajl_callbacks * callbacks,
           yajl_alloc_funcs * afs,
           void * ctx)
{
    yajl_handle hand = NULL;
    yajl_alloc_funcs afsBuffer;


    if (afs != NULL) {
        if (afs->malloc == NULL || afs->realloc == NULL || afs->free == NULL)
        {
            return NULL;
        }
    } else {
        yajl_set_default_alloc_funcs(&afsBuffer);
        afs = &afsBuffer;
    }

    hand = (yajl_handle) YA_MALLOC(afs, sizeof(struct yajl_handle_t));


    memcpy((void *) &(hand->alloc), (void *) afs, sizeof(yajl_alloc_funcs));

    hand->callbacks = callbacks;
    hand->ctx = ctx;
    hand->lexer = NULL;
    hand->bytesConsumed = 0;
    hand->decodeBuf = yajl_buf_alloc(&(hand->alloc));
    hand->flags	    = 0;
    yajl_bs_init(hand->stateStack, &(hand->alloc));
    yajl_bs_push(hand->stateStack, yajl_state_start);

    return hand;
}
