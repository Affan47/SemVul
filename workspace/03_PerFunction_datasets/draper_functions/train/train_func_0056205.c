gnc_commodity_get_mnemonic(const gnc_commodity * cm)
{
    if (!cm) return NULL;
    return GET_PRIVATE(cm)->mnemonic;
}
