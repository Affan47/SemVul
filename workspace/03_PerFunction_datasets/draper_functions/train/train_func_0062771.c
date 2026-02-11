write_to_data_file(osfildef *fp)
{
    char buf[16];


    oswp2(buf, get_prec(ext_));
    if (osfwb(fp, buf, 2))
        return 1;


    if (osfwb(fp, ext_, calc_alloc(get_prec(ext_))))
        return 1;


    return 0;
}
