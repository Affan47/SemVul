printpacket(const char* msg, const unsigned char* p, size_t len) {
    int i;
    printf("%s len=%d ", msg, len);
    for(i=0; i<len; ++i) {
        printf("%02x", p[i]);
    }
    printf("\n");
}
