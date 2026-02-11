iniMerge(char *data, const char *newdata)
{
    const char *p, *cb, *ce;
    char *section = 0, *key, *value;

    if (!newdata)
        return data;
    for (p = newdata;;) {
        for (; *p == ' ' || *p == '\t'; p++);
        if (!*p)
            break;
        if (*p == '\n') {
            p++;
            continue;
        }
        if (*p == '#') {
            for (p++; *p != '\n'; p++)
                if (!*p)
                    goto bail;
            p++;
            continue;
        }
        if (*p == '[') {
            cb = ++p;
            for (; *p != ']'; p++)
                if (!*p || *p == '\n')
                    goto bail;
            if (!reStrN(&section, cb, p - cb))
                break;
            p++;
        } else {
            cb = p;
            for (; *p != '='; p++)
                if (!*p || *p == '\n')
                    goto bail;
            for (ce = p; ce != cb && (*(ce - 1) == ' ' || *(ce - 1) == '\t'); ce--);
            if (!strNDup(&key, cb, ce - cb))
                break;
            for (p++; *p == ' ' || *p == '\t'; p++);
            cb = p;
            for (; *p && *p != '\n'; p++);
            for (ce = p; ce != cb && (*(ce - 1) == ' ' || *(ce - 1) == '\t'); ce--);
            if (!strNDup(&value, cb, ce - cb))
                break;
            if (section)
                data = iniEntry(data, section, key, value);
            free(value);
            free(key);
        }
    }
  bail:
    free(section);
    return data;
}
