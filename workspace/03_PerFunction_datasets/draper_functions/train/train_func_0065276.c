submit_work(struct thr_info *thr, const struct work *work_in) {
    struct workio_cmd *wc;


    wc = calloc(1, sizeof(*wc));
    if (!wc)
        return false;

    wc->u.work = malloc(sizeof(*work_in));
    if (!wc->u.work)
        goto err_out;

    wc->cmd = WC_SUBMIT_WORK;
    wc->thr = thr;
    work_copy(wc->u.work, work_in);


    if (!tq_push(thr_info[work_thr_id].q, wc))
        goto err_out;

    return true;

    err_out: workio_cmd_free(wc);
    return false;
}
