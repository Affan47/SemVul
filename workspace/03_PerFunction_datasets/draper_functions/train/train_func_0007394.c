del_objs_half_refill(H5F_t *f, hid_t dxpl, H5HF_t **fh, fheap_test_param_t *tparam,
    fheap_heap_ids_t *keep_ids)
{
    unsigned char *wobj;
    haddr_t fh_addr = HADDR_UNDEF;
    size_t id_len;
    size_t half_nobjs;
    size_t obj_idx;
    size_t u;


    HDassert(fh);
    HDassert(*fh);
    HDassert(keep_ids);


    if(tparam->reopen_heap) {
        if(H5HF_get_heap_addr(*fh, &fh_addr) < 0)
            FAIL_STACK_ERROR
        if(!H5F_addr_defined(fh_addr))
            TEST_ERROR
    }


    if(H5HF_get_id_len(*fh, &id_len) < 0)
        FAIL_STACK_ERROR


    if(tparam->del_dir == FHEAP_DEL_FORWARD)
        obj_idx = 0;
    else
        obj_idx = keep_ids->num_ids - 1;
    half_nobjs = keep_ids->num_ids / 2;
    for(u = 0; u < half_nobjs; u++) {

        if(H5HF_remove(*fh, dxpl, &keep_ids->ids[id_len * obj_idx]) < 0)
            FAIL_STACK_ERROR


        if(reopen_heap(f, dxpl, fh, fh_addr, tparam) < 0)
            TEST_ERROR


        if(tparam->del_dir == FHEAP_DEL_FORWARD)
            obj_idx++;
        else
            obj_idx--;
    }


    if(tparam->del_dir == FHEAP_DEL_FORWARD)
        obj_idx = 0;
    else
        obj_idx = keep_ids->num_ids - 1;
    for(u = 0; u < half_nobjs; u++) {

        wobj = &shared_wobj_g[keep_ids->offs[obj_idx]];
        if(H5HF_insert(*fh, dxpl, keep_ids->lens[obj_idx], wobj, &keep_ids->ids[id_len * obj_idx]) < 0)
            FAIL_STACK_ERROR


        if(reopen_heap(f, dxpl, fh, fh_addr, tparam) < 0)
            TEST_ERROR


        if(tparam->del_dir == FHEAP_DEL_FORWARD)
            obj_idx++;
        else
            obj_idx--;
    }


    return(0);

error:
    return(1);
}
