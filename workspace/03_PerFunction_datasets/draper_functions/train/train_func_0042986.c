get_line(QIOSTATE *qp)
{
    static int count;
    char *p;

    p = QIOread(qp);
    count++;
    while (QIOtoolong(qp) || (p != NULL && strlen(p) >= MAX_DIR_LEN)) {
        warn("line %d too long", count);
        error_count++;
        p = QIOread(qp);
    }
    if (p == NULL) {
        if (QIOerror(qp)) {
            syswarn("read error");
            error_count++;
        }
        return NULL;
    }
    return p;
}
