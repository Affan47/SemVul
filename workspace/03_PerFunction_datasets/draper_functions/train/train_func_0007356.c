copy_separation_name(tiffsep_device * pdev,
                char * buffer, int max_size, int sep_num)
{
    int sep_size = pdev->devn_params.separations.names[sep_num].size;
    const byte *p = pdev->devn_params.separations.names[sep_num].data;
    int i;


    if (sep_size > max_size - 1)
        sep_size = max_size - 1;


    for (i=0; i < sep_size; i++)
        buffer[i] = (gp_file_name_good_char(p[i]) && p[i] != '%') ? p[i] : '_';
    buffer[sep_size] = 0;
}
