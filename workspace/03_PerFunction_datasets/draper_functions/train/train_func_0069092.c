H5O_clear(H5F_t *f, H5O_t *oh, hbool_t destroy)
{
    unsigned	u;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(oh);

#ifdef H5_HAVE_PARALLEL
    if ( ( oh->cache_info.is_dirty ) && ( ! destroy ) ) {

	size_t i;


	for ( i = 0; i < oh->nchunks; i++ ) {

            if ( H5O_chunk_serialize(f, oh, i) < 0 ) {

                HGOTO_ERROR(H5E_OHDR, H5E_CANTSERIALIZE, FAIL,
			    "unable to serialize object header chunk")
	    }
        }
    }
#endif


    for(u = 0; u < oh->nmesgs; u++)
        oh->mesg[u].dirty = FALSE;

#ifndef NDEBUG

    oh->ndecode_dirtied = 0;
#endif


    oh->cache_info.is_dirty = FALSE;

    if(destroy)
        if(H5O_dest(f, oh) < 0)
            HGOTO_ERROR(H5E_OHDR, H5E_CANTFREE, FAIL, "unable to destroy object header data")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
