get (bin64_t bin) {
    if (bin==bin64_t::NONE)
        return EMPTY;
    iterator i(this,bin,true);


    return *i;
}
