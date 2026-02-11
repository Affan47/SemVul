lsmooth_sift_in(void * const head, uint64_t const count, size_t const elsz,
                     int (* const cmp)(void const * const, void const * const))
{
    char * h = (char *) head;
    char * left;
    char * right;
    char * next;
    char temp[elsz];
    uint64_t next_size;


    if (2 > count) {
        return;
    }


    memcpy(temp, head, elsz);
    uint64_t c = (uint64_t) count;


    do {
        right = h - offset(1,elsz);
        left = right - offset(lp[c-2],elsz);

        if (0 < cmp(left, right)) {
            next = left;
            next_size = c - 1;
        } else {
            next = right;
            next_size = c - 2;
        }

        if (0 <= cmp(temp, next)) {
            break;
        }

        memcpy(h, next, elsz);
        h = next;
        c = next_size;
    } while (1 < c);

    memcpy(h, temp, elsz);
}
