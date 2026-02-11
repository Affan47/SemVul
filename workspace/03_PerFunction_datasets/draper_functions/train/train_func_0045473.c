pervec_(integer *n, doublereal *v, integer *p)
{

    static integer ii, now;
    static doublereal save, temp;
    static integer next;


    if (*n <= 0)
        return 0;

    for (ii = 0; ii < *n; ++ii) {
        if (p[ii] < 0)
            continue;

        next = p[ii];
        save = v[ii];
        while (p[next-1] >= 0) {
            temp = save;
            save = v[next-1];
            v[next-1] = temp;

            now = next;
            next = p[now-1];
            p[now-1] = -next;
        }
    }

    for (ii = 0; ii < *n; ++ii)
        p[ii] = -p[ii];

    return 0;
}
