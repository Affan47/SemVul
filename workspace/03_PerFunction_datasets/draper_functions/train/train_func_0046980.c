obj_visit(hid_t fapl, hbool_t new_format)
{
    ovisit_ud_t udata;
    hid_t fid = -1;
    hid_t gid = -1;

    if(new_format)
        TESTING("object visiting (w/new group format)")
    else
        TESTING("object visiting")


    if((fid = build_visit_file(fapl)) < 0) TEST_ERROR


    udata.idx = 0;
    udata.info = new_format ? ovisit0_new : ovisit0_old;
    if(H5Ovisit(fid, H5_INDEX_NAME, H5_ITER_INC, visit_obj_cb, &udata) < 0) FAIL_STACK_ERROR


    if((gid = H5Gopen2(fid, "/", H5P_DEFAULT)) < 0) FAIL_STACK_ERROR
    udata.idx = 0;
    udata.info = new_format ? ovisit0_new : ovisit0_old;
    if(H5Ovisit(gid, H5_INDEX_NAME, H5_ITER_INC, visit_obj_cb, &udata) < 0) FAIL_STACK_ERROR
    if(H5Gclose(gid) < 0) FAIL_STACK_ERROR


    if((gid = H5Gopen2(fid, "/Group1", H5P_DEFAULT)) < 0) FAIL_STACK_ERROR
    udata.idx = 0;
    udata.info = new_format ? ovisit1_new : ovisit1_old;
    if(H5Ovisit(gid, H5_INDEX_NAME, H5_ITER_INC, visit_obj_cb, &udata) < 0) FAIL_STACK_ERROR
    if(H5Gclose(gid) < 0) FAIL_STACK_ERROR

    if((gid = H5Gopen2(fid, "/Group1/Group2", H5P_DEFAULT)) < 0) FAIL_STACK_ERROR
    udata.idx = 0;
    udata.info = new_format ? ovisit2_new : ovisit2_old;
    if(H5Ovisit(gid, H5_INDEX_NAME, H5_ITER_INC, visit_obj_cb, &udata) < 0) FAIL_STACK_ERROR
    if(H5Gclose(gid) < 0) FAIL_STACK_ERROR


    if(H5Fclose(fid) < 0) TEST_ERROR

    PASSED();
    return 0;

error:
    H5E_BEGIN_TRY {
        H5Gclose(gid);
        H5Fclose(fid);
    } H5E_END_TRY;
    return -1;
}
