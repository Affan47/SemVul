sm_signature(sm_t sm, char *str) {
    if (sm->siglen == 0) {
        snprintf(&sm->signature[sm->siglen], 2048 - sm->siglen, "%s", str);
        sm->siglen += strlen(str);
    } else {
        snprintf(&sm->signature[sm->siglen], 2048 - sm->siglen, " %s", str);
        sm->siglen += strlen(str) + 1;
    }
}
