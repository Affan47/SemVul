sftk_isTrue(SFTKObject *object,CK_ATTRIBUTE_TYPE type)
{
    SFTKAttribute *attribute;
    PRBool tok = PR_FALSE;

    attribute=sftk_FindAttribute(object,type);
    if (attribute == NULL) { return PR_FALSE; }
    tok = (PRBool)(*(CK_BBOOL *)attribute->attrib.pValue);
    sftk_FreeAttribute(attribute);

    return tok;
}
