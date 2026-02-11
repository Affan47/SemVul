getp_negate(VMG_ vm_obj_id_t self,
                              vm_val_t *retval, uint *argc)
{
    static CVmNativeCodeDesc desc(0);


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    neg_val(vmg_ retval, self);


    return TRUE;
}
