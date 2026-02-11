image_hash_name(char *str, int tablesize) {
    uint32 hash = 0;
    char *p;


    for (p = str; *p!='\0' && *p != '.'; p++) {
        hash += *p;
        hash += hash << 10;
        hash ^= hash >>  6;
    }
    hash += hash <<  3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash % tablesize;
}
