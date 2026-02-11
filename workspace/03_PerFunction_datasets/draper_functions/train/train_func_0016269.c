decodeNextUnicodeCharacter(std::string::const_iterator& it,
                             const std::string::const_iterator& e)
{
    boost::uint32_t uc;


#define FIRST_BYTE(mask, shift)        \
     \
    uc = (*it++ & (mask)) << (shift);

#define NEXT_BYTE(shift)                        \
                    \
    if (it == e || *it == 0) return 0;     \
    if ((*it & 0xC0) != 0x80) return invalid;     \
            \
    uc |= (*it++ & 0x3F) << shift;

    if (it == e || *it == 0) return 0;


    if ((*it & 0x80) == 0) return static_cast<boost::uint32_t>(*it++);


    if ((*it & 0xE0) == 0xC0) {

        FIRST_BYTE(0x1F, 6);
        NEXT_BYTE(0);
        if (uc < 0x80) return invalid;
        return uc;
    }
    else if ((*it & 0xF0) == 0xE0) {

        FIRST_BYTE(0x0F, 12);
        NEXT_BYTE(6);
        NEXT_BYTE(0);
        if (uc < 0x800) {
            return invalid;
        }
        return uc;
    }
    else if ((*it & 0xF8) == 0xF0) {

        FIRST_BYTE(0x07, 18);
        NEXT_BYTE(12);
        NEXT_BYTE(6);
        NEXT_BYTE(0);
        if (uc < 0x010000) return invalid;
        return uc;
    }
    else {

        it++;
        return invalid;
    }
}
