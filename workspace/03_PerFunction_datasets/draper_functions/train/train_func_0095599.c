getp_len(VMG_ vm_val_t *retval, const vm_val_t *self_val,
                         const char *lst, uint *argc)
{
    static CVmNativeCodeDesc desc(0);


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    retval->set_int(vmb_get_len(lst));


    return TRUE;
}
