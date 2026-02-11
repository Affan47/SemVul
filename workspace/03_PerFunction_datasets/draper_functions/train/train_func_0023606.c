calc_asin_series(char *ext1, char *ext2,
                                     char *ext3, char *ext4, char *ext5)
{
    ulong n;


    copy_val(ext2, ext1, FALSE);


    compute_prod_into(ext3, ext1, ext1);


    n = 1;


    for (;;)
    {
        ulong i;
        char *tmp;


        n += 2;


        copy_val(ext4, get_one(), FALSE);


        for (i = 3 ; i < n ; i += 2)
            mul_by_long(ext4, i);


        for (i = 2 ; i < n ; i += 2)
            div_by_long(ext4, i);


        div_by_long(ext4, n);


        compute_prod_into(ext5, ext2, ext3);


        tmp = ext5;
        ext5 = ext2;
        ext2 = tmp;


        compute_prod_into(ext5, ext2, ext4);


        if (is_zero(ext5)
            || get_exp(ext1) - get_exp(ext5) > (int)get_prec(ext1))
            break;


        compute_sum_into(ext4, ext1, ext5);


        tmp = ext4;
        ext4 = ext1;
        ext1 = tmp;
    }


    return ext1;
}
