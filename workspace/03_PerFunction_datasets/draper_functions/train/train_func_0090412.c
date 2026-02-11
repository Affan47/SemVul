create_s(void) {
    symbol * p;
    void * mem = malloc(HEAD + (CREATE_SIZE + 1) * sizeof(symbol));
    if (mem == NULL) return NULL;
    p = (symbol *) (HEAD + (char *) mem);
    CAPACITY(p) = CREATE_SIZE;
    SET_SIZE(p, CREATE_SIZE);
    return p;
}
