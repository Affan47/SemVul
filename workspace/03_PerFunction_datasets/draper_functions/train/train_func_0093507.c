setup_el(const char * name) {
    EditLine * el = NULL;

    el = el_init(name, stdin, stdout, stderr);
    if (el != NULL) {
        el_set(el, EL_SIGNAL, 1);
        el_set(el, EL_PROMPT, get_prompt);
        el_set(el, EL_EDITOR, "emacs");
        el_set(el, EL_BIND, "-e", "^P", "ed-prev-history", NULL);
        el_set(el, EL_BIND, "-e", "^N", "ed-next-history", NULL);
        el_set(el, EL_ADDFN, "ed-complete", "completion", completion);
        el_set(el, EL_BIND, "^I", "ed-complete", NULL);
    }
    return el;
}
