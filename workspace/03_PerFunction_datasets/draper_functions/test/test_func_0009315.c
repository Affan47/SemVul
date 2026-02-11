unify_char(char c, int case_sensitive, int T_equal_U)
{
    if (!case_sensitive) {
        c = tolower(c);
    }

    if (T_equal_U) {
        if (c=='t') {
            c = 'u';
        }
        else if (c=='T') {
            c = 'U';
        }
    }

    if (c=='.') {
        c = '-';
    }

    return c;
}
