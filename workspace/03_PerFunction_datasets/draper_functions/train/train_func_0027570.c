cons_uniquify(VMG0_)
{
    size_t cnt;
    size_t src, dst;


    cnt = vmb_get_len(ext_);


    for (src = dst = 0 ; src < cnt ; ++src)
    {
        size_t idx;
        vm_val_t src_val;
        int found;


        index_list(vmg_ &src_val, ext_, src + 1);
        for (idx = 0, found = FALSE ; idx < dst ; ++idx)
        {
            vm_val_t idx_val;


            index_list(vmg_ &idx_val, ext_, idx + 1);


            if (src_val.equals(vmg_ &idx_val))
            {

                found = TRUE;


                break;
            }
        }


        if (!found)
        {

            cons_set_element(dst, &src_val);


            ++dst;
        }
    }


    cons_set_len(dst);
}
