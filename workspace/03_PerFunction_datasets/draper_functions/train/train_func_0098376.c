getp_starts_with(VMG_ vm_val_t *retval,
                                   const vm_val_t *self_val,
                                   const char *str, uint *argc)
{
    static CVmNativeCodeDesc desc(1);
    const char *str2;
    size_t len;
    size_t len2;


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    str2 = CVmBif::pop_str_val(vmg0_);


    len = vmb_get_len(str);
    len2 = vmb_get_len(str2);


    str += VMB_LEN;
    str2 += VMB_LEN;


    retval->set_logical(len2 <= len && memcmp(str, str2, len2) == 0);


    return TRUE;
}
