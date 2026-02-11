get_block_dtu_param(Block *bpt, const int entry, dt_kind kind)
{
    List *param_head;
    Entry_kind ek = {entry, kind};
    Dtu_parameter *param;

    if (bpt == NULL || bpt->cmp_localize == NULL) return NULL;

    param_head = bpt->cmp_localize->param_head;

    param = list_lookup(param_head, cmp_dtu_param_entry_kind, &ek);

    return param;
}
