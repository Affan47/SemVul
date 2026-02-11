get_paramEntry(char *name)
{
    static struct targetParamTable_struct *ptr;
    for (ptr = aPTable; ptr; ptr = ptr->next) {
        if (strcmp(ptr->paramName, name) == 0) {
            return ptr;
        }
    }
    return NULL;
}
