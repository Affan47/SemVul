qvector_debug(qvector_t *vector, FILE *out) {
    if (out == NULL) {
        errno = EIO;
        return false;
    }

    vector->lock(vector);
    int i;
    for (i = 0; i < vector->num; i++) {
        void *data = (unsigned char  *)vector->data + i * vector->objsize;
        fprintf(out, "%d=", i);
        _q_textout(out, data, vector->objsize, MAX_HUMANOUT);
        fprintf(out, " (%zu)\n", vector->objsize);
    }
    vector->unlock(vector);

    return true;
}
