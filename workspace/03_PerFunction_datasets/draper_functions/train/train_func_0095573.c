circ_buf_resize(struct circ_buf_t *cb, int num)
{
    int data_len, tmp_len;
    char *tmp_buf;

    if (cb == NULL)
        return;


    if (cb->wpos == cb->rpos) {

        data_len = 0;
    } else if (cb->wpos > cb->rpos) {


        data_len = (char *) cb->wpos - (char *) cb->rpos;
        memmove(cb->start, cb->rpos, data_len);
    } else {

        data_len =
            cb->len * cb->size - ((char *) cb->rpos - (char *) cb->wpos);


        tmp_len = (char *) cb->wpos - (char *) cb->start;
        tmp_buf = (char *) safe_malloc("tmp_buf", tmp_len);
        memcpy(tmp_buf, cb->start, tmp_len);


        memmove(cb->start, cb->rpos, data_len - tmp_len);


        memcpy((char *) cb->start + data_len - tmp_len, tmp_buf, tmp_len);


        free(tmp_buf);
    }


    cb->len = num;
    cb->start = safe_realloc("cb->start", cb->start, cb->size * cb->len);
    cb->end = (void *) ((char *) cb->start + cb->size * cb->len);
    cb->rpos = cb->start;
    cb->wpos = (char *) cb->start + data_len;
}
