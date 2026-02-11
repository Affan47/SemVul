H5A_compact_build_table(H5F_t *f, hid_t dxpl_id, H5O_t *oh, H5_index_t idx_type,
    H5_iter_order_t order, H5A_attr_table_t *atable)
{
    H5A_compact_bt_ud_t udata;
    H5O_mesg_operator_t op;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(f);
    HDassert(oh);
    HDassert(atable);


    atable->attrs = NULL;
    atable->nattrs = 0;


    udata.f = f;
    udata.dxpl_id = dxpl_id;
    udata.atable = atable;
    udata.curr_attr = 0;
    udata.bogus_crt_idx = (hbool_t)((oh->version == H5O_VERSION_1 ||
            !(oh->flags & H5O_HDR_ATTR_CRT_ORDER_TRACKED)) ? TRUE : FALSE);


    op.op_type = H5O_MESG_OP_LIB;
    op.u.lib_op = H5A__compact_build_table_cb;
    if(H5O_msg_iterate_real(f, oh, H5O_MSG_ATTR, &op, &udata, dxpl_id) < 0)
        HGOTO_ERROR(H5E_ATTR, H5E_BADITER, FAIL, "error building attribute table")


    atable->nattrs = udata.curr_attr;


    if(atable->nattrs > 0) {

        if(H5A__attr_sort_table(atable, idx_type, order) < 0)
            HGOTO_ERROR(H5E_ATTR, H5E_CANTSORT, FAIL, "error sorting attribute table")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
