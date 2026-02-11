_ba_iterator_curr(binary_array_iterator *it)
{
    if(NULL == it) {
        netsnmp_assert(NULL != it);
        return NULL;
    }

    return _ba_iterator_position(it, it->pos);
}
