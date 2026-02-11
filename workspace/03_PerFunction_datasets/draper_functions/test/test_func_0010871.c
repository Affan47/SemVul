MakeBasicRfmType(TypeDict type_dict)
{
    RfmAttr attr;
    RfmType type;
    RfmType new;

    if (type_dict == NULL) {
        return(NULL);
    }
    if (!IsBasicRfmAttrFromTypeDict(type_dict, &attr)) {
        return(NULL);
    }
    type = RFM_Global->basic_type[attr];
    if (type) {
        if (type->type_dict == type_dict) {
            return(type);
        } else {
            MSG_LOGICALERROR;
            return(NULL);
        }
    }
    new = GET_RFM_TYPE_TABLE();
    new->type_dict = type_dict;
    new->attr = attr;
    RFM_Global->basic_type[attr] = new;
    return(new);
}
