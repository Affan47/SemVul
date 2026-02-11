find(const cxxtools::Char* token, size_type pos, size_type n) const
{
    const size_type size = this->size();
    const cxxtools::Char* str = privdata_ro();

    for( ; pos + n <= size; ++pos) {
        if( 0 == traits_type::compare( str + pos, token, n ) ) {
            return pos;
        }
    }

    return npos;
}
