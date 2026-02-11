getp_get_next(VMG_ vm_obj_id_t self, vm_val_t *retval,
                                 uint *argc)
{
    long idx;
    static CVmNativeCodeDesc desc(0);


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    idx = get_cur_index() + 1;


    if (idx > get_last_valid())
        err_throw(VMERR_OUT_OF_RANGE);


    get_indexed_val(vmg_ idx, retval);


    set_cur_index(vmg_ self, idx);


    return TRUE;
}
