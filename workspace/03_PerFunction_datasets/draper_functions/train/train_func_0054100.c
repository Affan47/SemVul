H5IMget_npalettes( hid_t loc_id,
                         const char *image_name,
                         hssize_t *npals )
{
    hid_t       did;
    hid_t       atid;
    hid_t       aid;
    hid_t       asid;
    H5T_class_t aclass;
    int         has_pal;


    *npals = 0;


    if((did = H5Dopen2(loc_id, image_name, H5P_DEFAULT)) < 0)
        return -1;


    has_pal = H5IM_find_palette(did);

    if(has_pal ==  1 )
    {

        if((aid = H5Aopen(did, "PALETTE", H5P_DEFAULT)) < 0)
            goto out;

        if((atid = H5Aget_type(aid)) < 0)
            goto out;

        if((aclass = H5Tget_class(atid)) < 0)
            goto out;


        if(aclass == H5T_REFERENCE)
        {
            if((asid = H5Aget_space(aid)) < 0)
                goto out;

            *npals = H5Sget_simple_extent_npoints( asid );

            if ( H5Sclose( asid ) < 0)
                goto out;

        }

        if ( H5Tclose( atid ) < 0)
            goto out;


        if ( H5Aclose( aid ) < 0)
            goto out;

    }


    if ( H5Dclose( did ) < 0)
        return -1;

    return 0;

out:
    H5Dclose( did );
    return -1;

}
