list_end( LIST * l )
{
    return l ? list_begin( l ) + l->impl.size : 0;
}
