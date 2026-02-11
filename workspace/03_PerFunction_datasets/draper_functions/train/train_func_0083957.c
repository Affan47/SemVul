H5D__layout_meta_size(const H5F_t *f, const H5O_layout_t *layout, hbool_t include_compact_data)
{
    size_t                  ret_value;

    FUNC_ENTER_PACKAGE


    HDassert(f);
    HDassert(layout);

    ret_value = 1 +
                1;

    switch(layout->type) {
        case H5D_COMPACT:

            ret_value += 2;
            if(include_compact_data)
                ret_value += layout->storage.u.compact.size;
            break;

        case H5D_CONTIGUOUS:
            ret_value += H5F_SIZEOF_ADDR(f);
            ret_value += H5F_SIZEOF_SIZE(f);
            break;

        case H5D_CHUNKED:

            HDassert(layout->u.chunk.ndims > 0 && layout->u.chunk.ndims <= H5O_LAYOUT_NDIMS);
            ret_value++;


            ret_value += layout->u.chunk.ndims * 4;


            ret_value += H5F_SIZEOF_ADDR(f);
            break;

        case H5D_LAYOUT_ERROR:
        case H5D_NLAYOUTS:
        default:
            HGOTO_ERROR(H5E_OHDR, H5E_CANTENCODE, 0, "Invalid layout class")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
