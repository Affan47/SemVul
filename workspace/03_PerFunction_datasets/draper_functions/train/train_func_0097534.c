consume_stringpart(StringAccum& sa,
                                           const uint8_t* first,
                                           const uint8_t* last) {
    while ((state_ & st_partlenmask) && first != last) {
        int part = state_ & st_partlenmask;
        uint8_t tag = sa[sa.length() - part];
        if ((tag != '\\' && (*first & 0xC0) != 0x80)
            || (tag == '\\' && part == 6 && *first != '\\')
            || (tag == '\\' && part == 7 && *first != 'u')
            || (tag == '\\' && part != 1 && part != 6 && part != 7
                && !isxdigit(*first))) {
            state_ = st_error;
            break;
        }
        sa.append(*first);
        if ((tag != '\\' && part == 1 + (tag >= 0xE0) + (tag >= 0xF0))
            || (tag == '\\' && (part == 1 || part == 5 || part == 11))) {
            uint8_t buf[12];
            memcpy(buf, sa.end() - part - 1, part + 1);
            sa.adjust_length(-part - 1);
            state_ -= st_stringpart | part;
            str_ = sa.take_string();
            (void) consume_string(buf, buf + part + 1, String());
            if (state_ == st_error)
                break;
            sa = StringAccum::make_transfer(str_);
        } else
            ++state_;
        ++first;
    }
    return first;
}
