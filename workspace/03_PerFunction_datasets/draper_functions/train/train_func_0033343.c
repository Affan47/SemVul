outputfiles(int f)
{
    unsigned int n;
    struct filename *p;
    struct filename *q;
#ifdef WITH_RFC2640
    char *c_buf;
#endif

    if (!head) {
        return;
    }
    tail->down = NULL;
    tail = NULL;
    colwidth = (colwidth | 7U) + 1U;
    if (opt_l != 0 || opt_C == 0) {
        colwidth = 75U;
    }

    p = head;
    p->top = 1;
    if (colwidth > 75U) {
        n = filenames;
    } else {
        n = (filenames + (75U / colwidth) - 1U) / (75U / colwidth);
    }
    while (n && p) {
        p = p->down;
        if (p != NULL) {
            p->top = 0;
        }
        n--;
    }


    q = head;
    while (p) {
        p->top = q->top;
        q->right = p;
        q = q->down;
        p = p->down;
    }


    while (q) {
        q->right = NULL;
        q = q->down;
    }


    p = head;
    while (p && p->down && !p->down->top) {
        p = p->down;
    }
    if (p && p->down) {
        p->down = NULL;
    }


    p = head;
    while (p) {
        q = p;
        p = p->down;
        while (q) {
            char pad[6];
            char *tmp = (char *) q;

            if (q->right) {
                memset(pad, '\t', sizeof pad - 1U);
                pad[(sizeof pad) - 1] = 0;
                pad[(colwidth + 7U - strlen(q->line)) / 8] = 0;
            } else {
                pad[0] = '\r';
                pad[1] = '\n';
                pad[2] = 0;
            }
#ifdef WITH_RFC2640
        c_buf = charset_fs2client(q->line);
            wrstr(f, c_buf);
        free(c_buf);
#else
            wrstr(f, q->line);
#endif
            wrstr(f, pad);
            q = q->right;
            free(tmp);
        }
    }


    head = tail = NULL;
    colwidth = 0U;
    filenames = 0U;
}
