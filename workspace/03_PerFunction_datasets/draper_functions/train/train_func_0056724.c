op_stop(hid_t dset, unsigned dim, hid_t scale_id, void *visitor_data)
{

    dset = dset;
    dim = dim;
    scale_id = scale_id;

    if ( visitor_data != NULL ) {
        (*(int *)visitor_data)++;
    }


    return 1;
}
