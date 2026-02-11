replace_sub_data_var_with_value(const Sub_data *head, const int value)
{
    const Sub_data *spt;
    int elem;

    elem = 0;
    for (spt = head; spt != NULL; spt = spt->next) {
        elem += (spt->sub_a*value)/spt->sub_da;
        elem += spt->sub_b/spt->sub_db;
    }
    return elem;
}
