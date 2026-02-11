PrintTagName(char *buf, RfmType type)
{
    TypeDict  type_dict;
    IdentDict ident_dict;

    if ((buf == NULL) || (type == NULL)) {
        return(buf);
    }
    type_dict = type->type_dict;
    if ((type_dict->type_kind != TKIND_STRUCT) &&
        (type_dict->type_kind != TKIND_UNION)) {
        return(buf);
    }

    if ((type_dict->TYPE_TAG_NAME == NULL) ||
        (type_dict->TYPE_TAG_NAME->NAME_IDENT == NULL)) {
        if (FCV_Tag_Temp_No < 10) {
            buf += sprintf(buf, "<$rec%02d>", FCV_Tag_Temp_No++);
        } else {
            buf += sprintf(buf, "<$rec%02d>", FCV_Tag_Temp_No++);
        }
        return(buf);
    }
    ident_dict = type_dict->TYPE_TAG_NAME->NAME_IDENT;
    buf += sprintf(buf, "<%s>", ident_dict->string);
    return(buf);
}
