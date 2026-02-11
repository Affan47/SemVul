scan_bos_resize(i_ctx_t *i_ctx_p, scanner_state * pstate, uint new_size,
                uint index)
{
    scan_binary_state *const pbs = &pstate->s_ss.binary;
    uint old_size = da_size(&pstate->s_da);
    byte *old_base = pstate->s_da.base;
    byte *new_base = iresize_string(old_base, old_size, new_size,
                                    "scan_bos_resize");
    byte *relocated_base = new_base + (new_size - old_size);
    uint i;
    ref *aptr = pbs->bin_array.value.refs;

    if (new_base == 0)
        return 0;


    if (relocated_base != old_base)
        for (i = index; i != 0; i--, aptr++)
            if (r_has_type(aptr, t_string) && r_size(aptr) != 0)
                aptr->value.bytes =
                    aptr->value.bytes - old_base + relocated_base;
    return new_base;
}
