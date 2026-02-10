save_locale(struct augeas *aug) {
    if (aug->c_locale == NULL) {
        aug->c_locale = newlocale(LC_ALL_MASK, "C", NULL);
        ERR_NOMEM(aug->c_locale == NULL, aug);
    }

    aug->user_locale = uselocale(aug->c_locale);
 error:
    return;
}
