make_regexp(struct info *info, char *pat, int nocase) {
    struct regexp *regexp;

    make_ref(regexp);
    regexp->info = ref(info);

    make_ref(regexp->pattern);
    regexp->pattern->str = pat;
    regexp->nocase = nocase;
    return regexp;
}
