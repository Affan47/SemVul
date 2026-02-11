getHeader(struct headers *heads, const char *key){
    int i;
    for(i = 0; heads -> keys[i] != NULL && strcmp(heads -> keys[i], key); i++);
    return heads -> values[i];
}
