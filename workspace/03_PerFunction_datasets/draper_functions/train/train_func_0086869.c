getLabelDefinition(char *name)
{
    char      *result = NULL;
    labelElem *label = getLabel(name);
    if (NULL != label) {
        result = strdup(label->labelDef);
    }
    return result;
}
