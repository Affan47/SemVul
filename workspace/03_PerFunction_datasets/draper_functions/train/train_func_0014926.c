CORD_riter(CORD x, CORD_iter_fn f1, void * client_data)
{
    size_t len = CORD_len(x);
    if (len == 0) return(0);
    return(CORD_riter4(x, len - 1, f1, client_data));
}
