inspect1(struct strscanner *p)
{
    char buf[BUFSIZE];
    char *bp = buf;
    long len;

    if (p->curr == 0) return rb_str_new2("");
    if (p->curr > INSPECT_LENGTH) {
        strcpy(bp, "..."); bp += 3;
        len = INSPECT_LENGTH;
    }
    else {
        len = p->curr;
    }
    memcpy(bp, CURPTR(p) - len, len); bp += len;
    return rb_str_dump(rb_str_new(buf, bp - buf));
}
