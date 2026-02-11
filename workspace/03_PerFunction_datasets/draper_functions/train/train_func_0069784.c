H5S_hyper_convert(H5S_t *space)
{
    herr_t      ret_value=SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT

    HDassert(space);


    switch(H5S_GET_SELECT_TYPE(space)) {
        case H5S_SEL_ALL:

            {
                hsize_t tmp_start[H5O_LAYOUT_NDIMS];
                hsize_t tmp_stride[H5O_LAYOUT_NDIMS];
                hsize_t tmp_count[H5O_LAYOUT_NDIMS];
                hsize_t tmp_block[H5O_LAYOUT_NDIMS];
                unsigned u;


                for(u=0; u<space->extent.rank; u++) {
                    tmp_start[u]=0;
                    tmp_stride[u]=1;
                    tmp_count[u]=1;
                    tmp_block[u]=space->extent.size[u];
                }


                if(H5S_select_hyperslab(space,H5S_SELECT_SET,tmp_start,tmp_stride,tmp_count,tmp_block)<0)
                    HGOTO_ERROR(H5E_DATASPACE, H5E_CANTDELETE, FAIL, "can't convert selection")
            }
            break;

        case H5S_SEL_HYPERSLABS:
            break;

        case H5S_SEL_NONE:
        case H5S_SEL_POINTS:
        case H5S_SEL_ERROR:
        case H5S_SEL_N:
        default:
            HGOTO_ERROR(H5E_ARGS, H5E_UNSUPPORTED, FAIL, "can't convert to span tree selection")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
