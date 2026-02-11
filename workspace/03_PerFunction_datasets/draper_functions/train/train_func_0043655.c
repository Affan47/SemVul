H5Z_filter_fletcher32 (unsigned flags, size_t UNUSED cd_nelmts, const unsigned UNUSED cd_values[],
                     size_t nbytes, size_t *buf_size, void **buf)
{
    void    *outbuf = NULL;
    unsigned char *src = (unsigned char*)(*buf);
    uint32_t fletcher;
    uint32_t reversed_fletcher;
    uint8_t  c[4];
    uint8_t  tmp;
    size_t   ret_value;

    FUNC_ENTER_NOAPI(H5Z_filter_fletcher32, 0)

    assert(sizeof(uint32_t)>=4);

    if (flags & H5Z_FLAG_REVERSE) {


        if (!(flags & H5Z_FLAG_SKIP_EDC)) {
            unsigned char *tmp_src;
            size_t  src_nbytes = nbytes;
            uint32_t stored_fletcher;


            src_nbytes -= FLETCHER_LEN;
            tmp_src=src+src_nbytes;
            UINT32DECODE(tmp_src, stored_fletcher);


            fletcher = H5_checksum_fletcher32(src, src_nbytes);


            HDmemcpy(c, &fletcher, (size_t)4);

            tmp  = c[1];
            c[1] = c[0];
            c[0] = tmp;

            tmp  = c[3];
            c[3] = c[2];
            c[2] = tmp;

            HDmemcpy(&reversed_fletcher, c, (size_t)4);


            if(stored_fletcher != fletcher && stored_fletcher != reversed_fletcher)
	        HGOTO_ERROR(H5E_STORAGE, H5E_READERROR, 0, "data error detected by Fletcher32 checksum")
        }


        ret_value = nbytes-FLETCHER_LEN;
    } else {
        unsigned char *dst;


        fletcher = H5_checksum_fletcher32(src, nbytes);

	if (NULL==(dst=outbuf=H5MM_malloc(nbytes+FLETCHER_LEN)))
	    HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, 0, "unable to allocate Fletcher32 checksum destination buffer")


        HDmemcpy((void*)dst, (void*)(*buf), nbytes);


        dst += nbytes;
        UINT32ENCODE(dst, fletcher);


 	H5MM_xfree(*buf);


        *buf_size = nbytes + FLETCHER_LEN;
	*buf = outbuf;
	outbuf = NULL;
	ret_value = *buf_size;
    }

done:
    if(outbuf)
        H5MM_xfree(outbuf);
    FUNC_LEAVE_NOAPI(ret_value)
}
