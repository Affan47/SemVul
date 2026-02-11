constructSubItem(char *name, unsigned char type,
     DUL_SUBITEM * subItem, unsigned long *rtnLength)
{
    if (strlen(name) < 1 || strlen(name) > 64)
    {
        char buf[1024];
        sprintf(buf,"Illegal service parameter: %s", name);
        return makeDcmnetCondition(DULC_ILLEGALSERVICEPARAMETER, OF_error, buf);
    }
    subItem->type = type;
    subItem->rsv1 = 0;
    subItem->length = (unsigned short) strlen(name);
    (void) strcpy(subItem->data, name);

    *rtnLength = subItem->length + 4;
    return EC_Normal;
}
