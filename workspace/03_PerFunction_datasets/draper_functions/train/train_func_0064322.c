ReformBasicType(void)
{
    TypeDict type_dict;
    int         i;

    for (i=0; i<DETAILS_MAX_NUM; i++) {
        type_dict = commonp->type_dict_tbl[i];
        if (type_dict) {
            (void)MakeBasicRfmType(type_dict);
        }
    }
    (void)MakeLogicalRfmType();
}
