load_mres_link(ulong siz, CVmImageLoaderMres *res_ifc)
{
    char buf[16];
    uint entry_cnt;
    uint i;


    read_data(buf, 2, &siz);
    entry_cnt = osrp2(buf);


    for (i = 0 ; i < entry_cnt ; ++i)
    {
        char buf[1];
        uint resname_len, fname_len;
        char resname_buf[256], fname_buf[256];


        read_data(buf, 1, &siz);
        resname_len = (uchar)buf[0];
        read_data(resname_buf, resname_len, &siz);
        resname_buf[resname_len] = '\0';


        read_data(buf, 1, &siz);
        fname_len = (uchar)buf[0];
        read_data(fname_buf, fname_len, &siz);
        fname_buf[fname_len] = '\0';


        res_ifc->add_resource(fname_buf, fname_len, resname_buf, resname_len);
    }


    if (siz != 0)
        fp_->skip_ahead(siz);
}
