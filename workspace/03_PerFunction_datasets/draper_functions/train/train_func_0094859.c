getp_get_size(VMG_ vm_obj_id_t self, vm_val_t *retval,
                              uint *argc)
{
    static CVmNativeCodeDesc desc(0);
    int is_res_file = ((get_ext()->flags & VMOBJFILE_IS_RESOURCE) != 0);


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    check_valid_file(vmg0_);


    note_file_seek(vmg_ self, TRUE);


    if (is_res_file)
    {

        retval->set_int(get_ext()->res_end - get_ext()->res_start + 1);
    }
    else
    {
        osfildef *fp = get_ext()->fp;
        unsigned long cur_pos;


        cur_pos = osfpos(fp);
        osfseek(fp, 0, OSFSK_END);


        retval->set_int(osfpos(fp));


        osfseek(fp, cur_pos, OSFSK_SET);
    }


    return TRUE;
}
