hattrie_iter_finished(hattrie_iter_t* i)
{
    return i->stack == NULL && i->i == NULL && !i->has_nil_key;
}
