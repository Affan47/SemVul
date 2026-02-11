getNextHdr(Buffer * b)
{
    int i;
    char c;

    for (i = b->ptr; b->ptr < b->length; ++b->ptr) {
        c = b->data[b->ptr];
        if (c == '\n' || c == '\r') {
            b->data[b->ptr] = 0;
            ++b->ptr;
            if (c == '\r' && b->ptr < b->length && b->data[b->ptr] == '\n') {
                b->data[b->ptr] = 0;
                ++b->ptr;
            }
            return &(b->data[i]);
        }
    }
    return NULL;
}
