getp_prepend(VMG_ vm_val_t *retval,
                             const vm_val_t *self_val,
                             const char *lst, uint *argc)
{
    static CVmNativeCodeDesc desc(1);


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    insert_elements(vmg_ retval, self_val, lst, 1, 0);


    return TRUE;
}
