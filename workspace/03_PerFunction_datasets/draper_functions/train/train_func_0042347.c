fs_ptable_chain_length(fs_ptable *pt, fs_row_id b, unsigned int max)
{
    if (b == 0) {
        fs_error(LOG_CRIT, "tried to read from chain 0\n");

        return 0;
    }
    if (b > pt->header->length) {
        fs_error(LOG_CRIT, "tried to read past end of ptable (%x, length=%x)\n", b, pt->header->length);

        return 0;
    }

    int length = 1;
    row *r = &(pt->data[b]);
    if (max) {
        while (r->cont != 0) {
            length++;
            r = &(pt->data[r->cont]);
            if (length > max) {
                fs_error(LOG_ERR, "max length (%d) exceeded", max);
                break;
            }
        }
    } else {
        while (r->cont != 0) {
            length++;
            r = &(pt->data[r->cont]);
        }
    }

    return length;
}
