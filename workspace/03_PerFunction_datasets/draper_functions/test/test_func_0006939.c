make_hlinks(hid_t loc_id)
{
    hid_t   g1id=-1;
    hid_t   g2id=-1;
    hid_t   g3id=-1;
    hsize_t dims[2]={3,2};
    int     buf[3][2]= {{1,1},{1,2},{2,2}};


    if(write_dset(loc_id, 2, dims, "dset", H5T_NATIVE_INT, buf) < 0)
        return -1;
    if(H5Lcreate_hard(loc_id, "dset", H5L_SAME_LOC, "link1 to dset", H5P_DEFAULT, H5P_DEFAULT) < 0)
        return -1;
    if(H5Lcreate_hard(loc_id, "dset", H5L_SAME_LOC, "link2 to dset", H5P_DEFAULT, H5P_DEFAULT) < 0)
        return -1;
    if(H5Lcreate_hard(loc_id, "dset", H5L_SAME_LOC, "link3 to dset", H5P_DEFAULT, H5P_DEFAULT) < 0)
        return -1;


    if((g1id = H5Gcreate2(loc_id, "g1", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0)
        goto out;
    if((g2id = H5Gcreate2(g1id, "g2", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0)
        goto out;
    if((g3id = H5Gcreate2(g2id, "g3", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0)
        goto out;

    if(H5Lcreate_hard(loc_id, "g1", g2id, "link1 to g1", H5P_DEFAULT, H5P_DEFAULT) < 0)
        goto out;
    if(H5Lcreate_hard(g1id, "g2", g3id, "link1 to g2", H5P_DEFAULT, H5P_DEFAULT) < 0)
        goto out;


    if (H5Gclose(g1id) < 0)
        goto out;
    if (H5Gclose(g2id) < 0)
        goto out;
    if (H5Gclose(g3id) < 0)
        goto out;

    return 0;

out:
    H5E_BEGIN_TRY
    {
        H5Gclose(g1id);
        H5Gclose(g2id);
        H5Gclose(g3id);
    } H5E_END_TRY;
    return -1;

}
