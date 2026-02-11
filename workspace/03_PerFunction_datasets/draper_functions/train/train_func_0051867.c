MakeLogicalRfmType(void)
{
    RfmType type;
    RfmType new;

    type = RFM_Global->basic_type[RFM_ATTR_LOGICAL];
    if (type) {
        return(type);
    }
    new = GET_RFM_TYPE_TABLE();
    new->attr = RFM_ATTR_LOGICAL;
    RFM_Global->basic_type[RFM_ATTR_LOGICAL] = new;
    return(new);
}
