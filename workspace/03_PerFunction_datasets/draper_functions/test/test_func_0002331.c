copyVars(char **envv, int index, MprHash *vars, cchar *prefix)
{
    MprKey  *kp;
    char    *cp;

    for (ITERATE_KEYS(vars, kp)) {
        if (kp->data) {
            if (prefix) {
                cp = sjoin(prefix, kp->key, "=", (char*) kp->data, NULL);
            } else {
                cp = sjoin(kp->key, "=", (char*) kp->data, NULL);
            }
            envv[index] = cp;
            for (; *cp != '='; cp++) {
                if (*cp == '-') {
                    *cp = '_';
                } else {
                    *cp = toupper((int) *cp);
                }
            }
            index++;
        }
    }
    envv[index] = 0;
    return index;
}
