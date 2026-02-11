getLabelPage(char *name)
{
    char      *result = NULL;
    labelElem *label = getLabel(name);
    if (NULL != label) {
        char *fullDef = strdup(label->labelDef);
        PushSource(NULL, fullDef);
        ignoreBraceParam();
        result = getBraceParam();
        PopSource();
        free(fullDef);
    }
    return result;
}
