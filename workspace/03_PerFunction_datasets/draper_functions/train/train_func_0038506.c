cbuf_reused (cbuf_t cb)
{


    int reused;

    assert(cb != NULL);
    cbuf_mutex_lock(cb);
    assert(cbuf_is_valid(cb));
    reused = (cb->i_out - cb->i_rep + (cb->size + 1)) % (cb->size + 1);
    cbuf_mutex_unlock(cb);
    return(reused);
}
