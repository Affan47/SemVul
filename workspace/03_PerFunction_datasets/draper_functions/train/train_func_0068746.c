MakeDummyRfmFunc(void)
{
    RfmFunc    prev;
    RfmFunc    func;
    RfmFunc    new;
    RfmProtArg arg;

    prev = NULL;
    for (func = RFM_Global->func_list;
         func != NULL;
         func = func->next) {
        prev = func;
    }
    new = GET_RFM_FUNC_TABLE();
    new->func_dict = NULL;
    new->ref_type = RFM_Global->basic_type[RFM_ATTR_INT];
    new->attr = RFM_ATTR_INT;
    new->is_dummy = TRUE;
    arg = MakeDummyRfmProtArg(new, NULL);
    (void)MakeDummyRfmProtArg(new, arg);
    if (prev) {
        prev->next = new;
        new->prev = prev;
    } else {
        RFM_Global->func_list = new;
    }
    return(new);
}
