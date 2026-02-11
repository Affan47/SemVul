alias_close(struct SResource *alias) {
    if (alias->u.fString.fChars != NULL) {
        uprv_free(alias->u.fString.fChars);
        alias->u.fString.fChars =NULL;
    }
}
