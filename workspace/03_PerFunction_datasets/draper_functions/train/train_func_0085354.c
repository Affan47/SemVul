insert_sug(char ***slst, char * word, int ns) {
    char * dup = mystrdup(word);
    if (!dup) return ns;
    if (ns == MAXSUGGESTION) {
        ns--;
        free((*slst)[ns]);
    }
    for (int k = ns; k > 0; k--) (*slst)[k] = (*slst)[k - 1];
    (*slst)[0] = dup;
    return ns + 1;
}
