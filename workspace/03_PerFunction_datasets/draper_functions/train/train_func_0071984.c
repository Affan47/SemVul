archive_compressor_compress_write(struct archive_write *a, const void *buff,
    size_t length)
{
    struct private_data *state;
    int i;
    int ratio;
    int c, disp, ret;
    const unsigned char *bp;

    state = (struct private_data *)a->compressor.data;
    if (a->client_writer == NULL) {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
            "No write callback is registered?  "
            "This is probably an internal programming error.");
        return (ARCHIVE_FATAL);
    }

    if (length == 0)
        return ARCHIVE_OK;

    bp = buff;

    if (state->in_count == 0) {
        state->cur_code = *bp++;
        ++state->in_count;
        --length;
    }

    while (length--) {
        c = *bp++;
        state->in_count++;
        state->cur_fcode = (c << 16) + state->cur_code;
        i = ((c << HSHIFT) ^ state->cur_code);

        if (state->hashtab[i] == state->cur_fcode) {
            state->cur_code = state->codetab[i];
            continue;
        }
        if (state->hashtab[i] < 0)
            goto nomatch;

        if (i == 0)
            disp = 1;
        else
            disp = HSIZE - i;
 probe:
        if ((i -= disp) < 0)
            i += HSIZE;

        if (state->hashtab[i] == state->cur_fcode) {
            state->cur_code = state->codetab[i];
            continue;
        }
        if (state->hashtab[i] >= 0)
            goto probe;
 nomatch:
        ret = output_code(a, state->cur_code);
        if (ret != ARCHIVE_OK)
            return ret;
        state->cur_code = c;
        if (state->first_free < state->max_maxcode) {
            state->codetab[i] = state->first_free++;
            state->hashtab[i] = state->cur_fcode;
            continue;
        }
        if (state->in_count < state->checkpoint)
            continue;

        state->checkpoint = state->in_count + CHECK_GAP;

        if (state->in_count <= 0x007fffff)
            ratio = state->in_count * 256 / state->out_count;
        else if ((ratio = state->out_count / 256) == 0)
            ratio = 0x7fffffff;
        else
            ratio = state->in_count / ratio;

        if (ratio > state->compress_ratio)
            state->compress_ratio = ratio;
        else {
            state->compress_ratio = 0;
            memset(state->hashtab, 0xff, sizeof(state->hashtab));
            state->first_free = FIRST;
            ret = output_code(a, CLEAR);
            if (ret != ARCHIVE_OK)
                return ret;
        }
    }

    return (ARCHIVE_OK);
}
