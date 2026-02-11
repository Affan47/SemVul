DB_GetUIDTag (DB_LEVEL level, DcmTagKey *tag)
{
    int i;

    for (i = 0; i < NbFindAttr; i++)
    if ((TbFindAttr[i]. level == level) && (TbFindAttr[i]. keyAttr == UNIQUE_KEY))
        break;

    if (i < NbFindAttr) {
        *tag = TbFindAttr[i].tag;
        return (EC_Normal);
    }
    else
    return (DcmQRIndexDatabaseError);

}
