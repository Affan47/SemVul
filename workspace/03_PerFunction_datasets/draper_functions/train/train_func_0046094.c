compute_sinhcosh_into(VMG_ char *dst, const char *src,
                                         int is_cosh, int is_tanh)
{
    size_t prec = get_prec(dst);
    uint hdl1, hdl2, hdl3, hdl4;
    char *ext1, *ext2, *ext3, *ext4;


    alloc_temp_regs(vmg_ prec + 3, 4,
                    &ext1, &hdl1, &ext2, &hdl2, &ext3, &hdl3,
                    &ext4, &hdl4);


    err_try
    {


        compute_exp_into(vmg_ ext1, src);


        copy_val(ext3, get_one(), FALSE);
        compute_quotient_into(vmg_ ext2, 0, ext3, ext1);


        if (is_tanh)
        {

            compute_sum_into(ext4, ext1, ext2);


            negate(ext2);
            compute_sum_into(ext3, ext1, ext2);


            compute_quotient_into(vmg_ ext1, 0, ext3, ext4);


            ext3 = ext1;
        }
        else
        {


            if (!is_cosh)
                negate(ext2);


            compute_sum_into(ext3, ext1, ext2);


            div_by_long(ext3, 2);
        }


        copy_val(dst, ext3, TRUE);
    }
    err_finally
    {

        release_temp_regs(vmg_ 4, hdl1, hdl2, hdl3, hdl4);
    }
    err_end;
}
