test_big_table(hid_t fid)
{
    herr_t err;
    hid_t table;
    hid_t part_t;
    size_t c;
    particle_t readPart;
    hsize_t count;

    TESTING("large packet table");


    part_t = make_particle_type();

    HDassert(part_t != -1);


    table = H5PTcreate_fl(fid, "Packet Test Dataset2", part_t, (hsize_t)33, -1);
    H5Tclose(part_t);
    if( H5PTis_valid(table) < 0)
        goto out;


    for(c = 0; c < BIG_TABLE_SIZE ; c+=8)
    {

        err = H5PTappend(table, (size_t)8, &(testPart[0]));
        if( err < 0)
            goto out;
    }


    err = H5PTget_num_packets(table, &count);
    if( err < 0)
        goto out;
    if( count != BIG_TABLE_SIZE )
        goto out;


    for(c = 0; c < BIG_TABLE_SIZE; c++)
    {
        err = H5PTget_next(table, 1, &readPart);
        if(err < 0)
            goto out;


        if( cmp_par(c % 8, 0, testPart, &readPart) != 0)
            goto out;
    }


    err = H5PTclose(table);
    if( err < 0)
        goto out;

    PASSED();
    return 0;

    out:
        H5_FAILED();
        if( H5PTis_valid(table) < 0)
            H5PTclose(table);
        return -1;
}
