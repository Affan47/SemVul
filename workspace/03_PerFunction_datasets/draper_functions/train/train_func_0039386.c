epr_trim_string(char* str)
{
    int i, i1, i2, n;

    assert(str != NULL);

    n = strlen(str);
    if (n == 0)
        return str;

    i1 = -1;
    for (i = 0; str[i] != '\0'; i++) {
        if (!isspace(str[i])) {
            i1 = i;
            break;
        }
    }

    if (i1 == -1) {
        str[0] = '\0';
        return str;
    }

    i2 = -1;
    for (i = n - 1; i >= 0; i--) {
        if (!isspace(str[i])) {
            i2 = i;
            break;
        }
    }

    assert(i1 > -1 && i2 > -1);

    if (i1 > 0) {
        int j = 0;
        for (i = i1; i <= i2; i++) {
            str[j] = str[i];
            j++;
        }
    }

    str[i2 - i1 + 1] = '\0';

    return str;
}
