H5O__dset_bh_info(H5F_t *f, hid_t dxpl_id, H5O_t *oh, H5_ih_info_t *bh_info)
{
    H5O_layout_t        layout;
    H5O_pline_t         pline;
    H5O_efl_t           efl;
    hbool_t             layout_read = FALSE;
    hbool_t             pline_read = FALSE;
    hbool_t             efl_read = FALSE;
    htri_t		exists;
    herr_t      	ret_value = SUCCEED;

    FUNC_ENTER_STATIC


    HDassert(f);
    HDassert(oh);
    HDassert(bh_info);


    if(NULL == H5O_msg_read_oh(f, dxpl_id, oh, H5O_LAYOUT_ID, &layout))
	HGOTO_ERROR(H5E_OHDR, H5E_CANTGET, FAIL, "can't find layout message")
    layout_read = TRUE;


    if(layout.type == H5D_CHUNKED && H5D__chunk_is_space_alloc(&layout.storage)) {

        if((exists = H5O_msg_exists_oh(oh, H5O_PLINE_ID)) < 0)
            HGOTO_ERROR(H5E_DATASET, H5E_CANTINIT, FAIL, "unable to read object header")
        else if(exists) {
            if(NULL == H5O_msg_read_oh(f, dxpl_id, oh, H5O_PLINE_ID, &pline))
                HGOTO_ERROR(H5E_OHDR, H5E_CANTGET, FAIL, "can't find I/O pipeline message")
            pline_read = TRUE;
        }
        else
            HDmemset(&pline, 0, sizeof(pline));

        if(H5D__chunk_bh_info(f, dxpl_id, &layout, &pline, &(bh_info->index_size)) < 0)
            HGOTO_ERROR(H5E_OHDR, H5E_CANTGET, FAIL, "can't determine chunked dataset btree info")
    }


    if((exists = H5O_msg_exists_oh(oh, H5O_EFL_ID)) < 0)
	HGOTO_ERROR(H5E_OHDR, H5E_NOTFOUND, FAIL, "unable to check for EFL message")

    if(exists && H5D__efl_is_space_alloc(&layout.storage)) {

        HDmemset(&efl, 0, sizeof(efl));


	if(NULL == H5O_msg_read_oh(f, dxpl_id, oh, H5O_EFL_ID, &efl))
	    HGOTO_ERROR(H5E_OHDR, H5E_CANTGET, FAIL, "can't find EFL message")
        efl_read = TRUE;


	if(H5D__efl_bh_info(f, dxpl_id, &efl, &(bh_info->heap_size)) < 0)
            HGOTO_ERROR(H5E_OHDR, H5E_CANTGET, FAIL, "can't determine EFL heap info")
    }

done:

    if(layout_read && H5O_msg_reset(H5O_LAYOUT_ID, &layout) < 0)
        HDONE_ERROR(H5E_DATASET, H5E_CANTRESET, FAIL, "unable to reset data storage layout message")
    if(pline_read && H5O_msg_reset(H5O_PLINE_ID, &pline) < 0)
        HDONE_ERROR(H5E_DATASET, H5E_CANTRESET, FAIL, "unable to reset I/O pipeline message")
    if(efl_read && H5O_msg_reset(H5O_EFL_ID, &efl) < 0)
        HDONE_ERROR(H5E_DATASET, H5E_CANTRESET, FAIL, "unable to reset external file list message")

    FUNC_LEAVE_NOAPI(ret_value)
}
