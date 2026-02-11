aug_to_xml(const struct augeas *aug, const char *pathin,
               xmlNode **xmldoc, unsigned int flags) {
    struct pathx *p;
    int result;

    api_entry(aug);

    ARG_CHECK(flags != 0, aug, "aug_to_xml: FLAGS must be 0");
    ARG_CHECK(xmldoc == NULL, aug, "aug_to_xml: XMLDOC must be non-NULL");

    if (pathin == NULL || strlen(pathin) == 0 || strcmp(pathin, "/") == 0) {
        pathin = "/*";
    }

    p = pathx_aug_parse(aug, aug->origin, tree_root_ctx(aug), pathin, true);
    ERR_BAIL(aug);
    result = tree_to_xml(p, xmldoc, pathin);
    ERR_THROW(result < 0, aug, AUG_ENOMEM, NULL);
    free_pathx(p);
    api_exit(aug);

    return result;
 error:
    if (xmldoc !=NULL)
        *xmldoc = NULL;
    api_exit(aug);
    return -1;
}
