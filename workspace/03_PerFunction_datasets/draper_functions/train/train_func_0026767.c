hex2int(unsigned short c, bool* error)
{
    if ( c >= '0' && c <= '9' ) {
        return c - '0';
    } else if ( c >= 'A' && c <= 'F' ) {
        return 10 + c - 'A';
    } else if ( c >= 'a' && c <= 'f' ) {
        return 10 + c - 'a';
    } else {
        *error = true;
        return -1;
    }
}
