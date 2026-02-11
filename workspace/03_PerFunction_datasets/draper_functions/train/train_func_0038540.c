compute_init_2op(VMG_ vm_val_t *result,
                                     const char *ext1, const char *ext2)
{
    size_t new_prec;
    char *new_ext;


    new_prec = get_prec(ext1);
    if (get_prec(ext2) > new_prec)
        new_prec = get_prec(ext2);


    if (is_nan(ext1) || is_nan(ext2))
        new_prec = 1;


    result->set_obj(create(vmg_ FALSE, new_prec));


    new_ext = get_objid_ext(vmg_ result->val.obj);


    if (get_type(ext1) != VMBN_T_NUM)
    {

        set_type(new_ext, get_type(ext1));
        set_neg(new_ext, get_neg(ext1));


        return 0;
    }


    if (get_type(ext2) != VMBN_T_NUM)
    {

        set_type(new_ext, get_type(ext2));
        set_neg(new_ext, get_neg(ext2));


        return 0;
    }


    return new_ext;
}
