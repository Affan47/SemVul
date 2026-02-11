rfind(cxxtools::Char ch, size_type pos) const
{
    const cxxtools::Char* str = privdata_ro();
    size_type size = this->size();

    if(size == 0)
        return npos;

    if(--size > pos)
        size = pos;

    for(++size; size-- > 0; ) {
        if( traits_type::eq(str[size], ch) )
            return size;
    }

    return npos;
}
