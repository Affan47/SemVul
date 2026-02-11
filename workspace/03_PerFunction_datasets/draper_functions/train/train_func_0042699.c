H5A_dense_exists(H5F_t *f, hid_t dxpl_id, const H5O_ainfo_t *ainfo, const char *name)
{
    H5A_bt2_ud_common_t udata;
    H5HF_t *fheap = NULL;
    H5HF_t *shared_fheap = NULL;
    H5B2_t *bt2_name = NULL;
    htri_t attr_sharable;
    htri_t ret_value = TRUE;

    FUNC_ENTER_NOAPI(H5A_dense_exists, NULL)


    HDassert(f);
    HDassert(ainfo);
    HDassert(name);


    if(NULL == (fheap = H5HF_open(f, dxpl_id, ainfo->fheap_addr)))
        HGOTO_ERROR(H5E_ATTR, H5E_CANTOPENOBJ, FAIL, "unable to open fractal heap")


    if((attr_sharable = H5SM_type_shared(f, H5O_ATTR_ID, dxpl_id)) < 0)
        HGOTO_ERROR(H5E_ATTR, H5E_CANTGET, FAIL, "can't determine if attributes are shared")


    if(attr_sharable) {
        haddr_t shared_fheap_addr;


        if(H5SM_get_fheap_addr(f, dxpl_id, H5O_ATTR_ID, &shared_fheap_addr) < 0)
            HGOTO_ERROR(H5E_ATTR, H5E_CANTGET, FAIL, "can't get shared message heap address")


        if(H5F_addr_defined(shared_fheap_addr)) {

            if(NULL == (shared_fheap = H5HF_open(f, dxpl_id, shared_fheap_addr)))
                HGOTO_ERROR(H5E_ATTR, H5E_CANTOPENOBJ, FAIL, "unable to open fractal heap")
        }
    }


    if(NULL == (bt2_name = H5B2_open(f, dxpl_id, ainfo->name_bt2_addr, NULL)))
        HGOTO_ERROR(H5E_ATTR, H5E_CANTOPENOBJ, FAIL, "unable to open v2 B-tree for name index")


    udata.f = f;
    udata.dxpl_id = dxpl_id;
    udata.fheap = fheap;
    udata.shared_fheap = shared_fheap;
    udata.name = name;
    udata.name_hash = H5_checksum_lookup3(name, HDstrlen(name), 0);
    udata.flags = 0;
    udata.corder = 0;
    udata.found_op = NULL;
    udata.found_op_data = NULL;


    if((ret_value = H5B2_find(bt2_name, dxpl_id, &udata, NULL, NULL)) < 0)
        HGOTO_ERROR(H5E_ATTR, H5E_NOTFOUND, FAIL, "can't search for attribute in name index")

done:

    if(shared_fheap && H5HF_close(shared_fheap, dxpl_id) < 0)
        HDONE_ERROR(H5E_ATTR, H5E_CLOSEERROR, FAIL, "can't close fractal heap")
    if(fheap && H5HF_close(fheap, dxpl_id) < 0)
        HDONE_ERROR(H5E_ATTR, H5E_CLOSEERROR, FAIL, "can't close fractal heap")
    if(bt2_name && H5B2_close(bt2_name, dxpl_id) < 0)
        HDONE_ERROR(H5E_ATTR, H5E_CLOSEERROR, FAIL, "can't close v2 B-tree for name index")

    FUNC_LEAVE_NOAPI(ret_value)
}
