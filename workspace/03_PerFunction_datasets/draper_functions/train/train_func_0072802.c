PR_ProcessAttrSetCurrentDirectory(
    PRProcessAttr *attr,
    const char *dir)
{
    PR_FREEIF(attr->currentDirectory);
    attr->currentDirectory = (char *) PR_MALLOC(strlen(dir) + 1);
    if (!attr->currentDirectory) {
        PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
        return PR_FAILURE;
    }
    strcpy(attr->currentDirectory, dir);
    return PR_SUCCESS;
}
