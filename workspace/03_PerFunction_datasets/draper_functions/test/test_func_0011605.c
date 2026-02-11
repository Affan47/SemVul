H5O_layout_encode(H5F_t *f, hbool_t UNUSED disable_shared, uint8_t *p, const void *_mesg)
{
    const H5O_layout_t     *mesg = (const H5O_layout_t *) _mesg;
    unsigned               u;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5O_layout_encode)


    HDassert(f);
    HDassert(mesg);
    HDassert(p);


    *p++ = (uint8_t)H5O_LAYOUT_VERSION_3;


    *p++ = mesg->type;


    switch(mesg->type) {
        case H5D_COMPACT:

            UINT16ENCODE(p, mesg->storage.u.compact.size);


            if(mesg->storage.u.compact.size > 0) {
                if(mesg->storage.u.compact.buf)
                    HDmemcpy(p, mesg->storage.u.compact.buf, mesg->storage.u.compact.size);
                else
                    HDmemset(p, 0, mesg->storage.u.compact.size);
                p += mesg->storage.u.compact.size;
            }
            break;

        case H5D_CONTIGUOUS:
            H5F_addr_encode(f, &p, mesg->storage.u.contig.addr);
            H5F_ENCODE_LENGTH(f, p, mesg->storage.u.contig.size);
            break;

        case H5D_CHUNKED:

            HDassert(mesg->u.chunk.ndims > 0 && mesg->u.chunk.ndims <= H5O_LAYOUT_NDIMS);
            *p++ = (uint8_t)mesg->u.chunk.ndims;


            H5F_addr_encode(f, &p, mesg->storage.u.chunk.idx_addr);


            for(u = 0; u < mesg->u.chunk.ndims; u++)
                UINT32ENCODE(p, mesg->u.chunk.dim[u]);
            break;

        default:
            HGOTO_ERROR(H5E_OHDR, H5E_CANTENCODE, FAIL, "Invalid layout class")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
