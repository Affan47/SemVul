enc_ensure(Encoder* e, size_t req)
{
    size_t need = e->curr->size;
    while(req >= (need - e->i)) need <<= 1;

    if(need != e->curr->size) {
        if(!enif_realloc_binary(e->curr, need)) {
            return 0;
        }
        e->p = (char*) e->curr->data;
        e->u = (unsigned char*) e->curr->data;
    }

    return 1;
}
