write(char *cp, int n)
{
    int rc = 0;
    Lock qlock(Q_mutex, false);

    if (lock)
        return -2;

    inWrite = 1;
    qlock.get();
    int idx = write_p;

    if (base_p[idx].rdy == false) {
        base_p[idx].qcp = (void*)cp;
        base_p[idx].qcmd = n;
        base_p[idx].rdy = true;
        idx++;
        itemsQueued++;
        if (idx >= size)
            idx = 0;

        write_p = idx;
    } else {
        overrun++ ;
        if (dyn) {
            delete[] cp;
            cp = NULL;
        }
        rc = -1;
    }

    qlock.release();
    inWrite = 0;
    return rc;
}
