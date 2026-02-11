find (const bin64_t range, fill_t seek) {
    iterator i(this,range,true);
    fill_t stop = seek==EMPTY ? FILLED : EMPTY;
    while (true) {
        while ( i.deep() || (*i!=stop && *i!=seek) )
            i.left();
        if (!i.deep() && *i==seek)
            return i.bin();
        while (i.bin().is_right() && i.bin()!=range)
            i.parent();
        if (i.bin()==range)
            break;
        i.parent();
        i.right();
    }
    return bin64_t::NONE;
}
