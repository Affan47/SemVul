getp_len(VMG_ vm_val_t *retval, const vm_val_t *self_val,
                           const char *str, uint *argc)
{
    utf8_ptr p;
    static CVmNativeCodeDesc desc(0);


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    p.set((char *)str + VMB_LEN);


    retval->set_int(p.len(vmb_get_len(str)));


    return TRUE;
}
