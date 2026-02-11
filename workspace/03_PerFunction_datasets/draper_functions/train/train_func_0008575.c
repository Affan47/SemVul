nibble(char c) {
    c = PORT_Tolower(c);
    return ( c >= '0' && c <= '9') ? c - '0' :
           ( c >= 'a' && c <= 'f') ? c - 'a' +10 : -1;
}
