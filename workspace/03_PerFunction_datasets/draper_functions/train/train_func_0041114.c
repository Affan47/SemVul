pr_GetR(XrmDatabase xrdb, char *resource)
{
    char name[128], class[128], *rc;

    strcpy(name, X_Name);
    strcat(name, resource);
    strcpy(class, X_Class);
    strcat(class, resource);
    rc = XrmGetResource(xrdb, name, class, type, &value)
	? (char *) value.addr : (char *) 0;
    return (rc);
}
