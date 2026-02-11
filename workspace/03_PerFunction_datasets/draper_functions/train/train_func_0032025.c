match(cchar *pattern, cchar *file)
{
    cchar   *pp, *fp;

    if (pattern == 0 || *pattern == '\0') {
        return 1;
    }
    if (file == 0 || *file == '\0') {
        return 0;
    }
    for (pp = pattern, fp = file; *pp; ) {
        if (*fp == '\0') {
            if (*pp == '*' && pp[1] == '\0') {

                return 1;
            }
            return 0;
        }

        if (*pp == '*') {
            if (match(&pp[1], &fp[0])) {
                return 1;
            }
            fp++;
            continue;

        } else if (*pp == '?' || *pp == *fp) {
            fp++;

        } else {
            return 0;
        }
        pp++;
    }
    if (*fp == '\0') {

        return 1;
    }
    return 0;
}
