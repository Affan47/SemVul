ompfbe_ddsche_write_setmt(fsbe_context *cx, Hmdf_context *hcx, int mt_no)
{
    if (opt_scheduler_module) {
        ddsche_write_setmt_module_call(
            cx,  hcx->hmdf,  hcx->clustering_number, hcx->pc_number, mt_no);
    } else {
        ompfbe_taskq_write_enqueue_intmt(
            cx, hcx->mtg_id, hcx->pc_number, mt_no);
    }
}
