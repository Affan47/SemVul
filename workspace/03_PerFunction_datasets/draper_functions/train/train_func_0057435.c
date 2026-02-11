num_bytes_in_utf8_sequence(unsigned char c) {
    if (c == 0xC0 || c == 0xC1 || c > 0xF4 || IS_CONT(c)) {
        return 0;
    } else if ((c & 0x80) == 0) {
        return 1;
    } else if ((c & 0xE0) == 0xC0) {
        return 2;
    } else if ((c & 0xF0) == 0xE0) {
        return 3;
    } else if ((c & 0xF8) == 0xF0) {
        return 4;
    }
    return 0;
}
