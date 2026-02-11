opvp_adjust_num_string(char *num_string)
{
    char *pp;
    char *lp;

    if (!num_string) return NULL;

    if ((pp = strrchr(num_string, '.'))) {
        for (lp = &(num_string[strlen(num_string)-1]); lp > pp; lp--) {
            if (*lp == '0') {
                *lp = '\0';
            } else {
                break;
            }
        }
        if (lp == pp) *lp = '\0';
    }

    return num_string;
}
