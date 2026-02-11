sarrayToStringRange(SARRAY  *sa,
                    l_int32  first,
                    l_int32  nstrings,
                    l_int32  addnlflag)
{
char    *dest, *src, *str;
l_int32  n, i, last, size, index, len;

    PROCNAME("sarrayToStringRange");

    if (!sa)
        return (char *)ERROR_PTR("sa not defined", procName, NULL);
    if (addnlflag != 0 && addnlflag != 1 && addnlflag != 2)
        return (char *)ERROR_PTR("invalid addnlflag", procName, NULL);

    n = sarrayGetCount(sa);


    if (n == 0) {
        if (first == 0) {
            if (addnlflag == 0)
                return stringNew("");
            if (addnlflag == 1)
                return stringNew("\n");
	    else
                return stringNew(" ");
        }
        else
            return (char *)ERROR_PTR("first not valid", procName, NULL);
    }

    if (first < 0 || first >= n)
        return (char *)ERROR_PTR("first not valid", procName, NULL);
    if (nstrings == 0 || (nstrings > n - first))
        nstrings = n - first;
    last = first + nstrings - 1;

    size = 0;
    for (i = first; i <= last; i++) {
        if ((str = sarrayGetString(sa, i, L_NOCOPY)) == NULL)
            return (char *)ERROR_PTR("str not found", procName, NULL);
        size += strlen(str) + 2;
    }

    if ((dest = (char *)CALLOC(size + 1, sizeof(char))) == NULL)
        return (char *)ERROR_PTR("dest not made", procName, NULL);

    index = 0;
    for (i = first; i <= last; i++) {
        src = sarrayGetString(sa, i, L_NOCOPY);
        len = strlen(src);
        memcpy(dest + index, src, len);
        index += len;
        if (addnlflag == 1) {
            dest[index] = '\n';
            index++;
        }
        else if (addnlflag == 2) {
            dest[index] = ' ';
            index++;
        }
    }

    return dest;
}
