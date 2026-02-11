gd_stage_op_req_free (gd1_mgmt_stage_op_req *req)
{
        if (!req)
                return;

        GF_FREE (req->buf.buf_val);
        GF_FREE (req);
}
