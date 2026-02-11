calc_kick_check_timing_margin(Stasche_lm_dt *sld, int smt, Pp spp, Ov ov,
                              int rmt, Pp rpp)
{
    real stime, rtime, time, kick_time;
    int spgno = sld->taskexepro[smt];
    int rpgno = sld->taskexepro[rmt];
    int sidx = get_timing_index(sld, smt, spp);
    int ridx = get_timing_index(sld, rmt, rpp);
    Ptm *tptm, *ret;
    if (ov == BODY) {
        stime = get_timing_time(sld, spgno, sidx);
        kick_time = get_timing_dt(sld, spgno, sidx);
    } else {
        stime = get_timing_overlap_dt_time(sld, spgno, sidx);
        kick_time = get_timing_overlap_dt(sld, spgno, sidx);
    }
    rtime = get_timing_time(sld, rpgno, ridx);
    time = rtime - stime;
    ret = zcalloc(1, sizeof(Ptm));
    ret->pp = spp;
    ret->mtno = smt;
    ret->ov = ov;
    sld->kick_timing[rmt][rpp] = list_append(sld->kick_timing[rmt][rpp], ret);
    tptm = list_lookup(sld->check_timing[rmt][rpp], cmp_ptm, ret);
    if (tptm != NULL) {
        real mk_time, mc_time;
        if (tptm->ov == BODY) {
            mk_time = get_timing_time(sld, spgno, sidx)
                - get_timing_dt(sld, spgno, sidx) + tptm->kick_time;
        } else {
            mk_time = get_timing_time(sld, spgno, sidx) + tptm->kick_time;
        }
        mc_time = get_timing_time(sld, rpgno, ridx)
            - get_timing_dt(sld, rpgno, ridx) + tptm->check_time;
        if (mc_time - mk_time > time) {
            tptm->kick_time = kick_time;
            tptm->check_time = get_timing_dt(sld, rpgno, ridx);
        }
    } else {
        ret = zcalloc(1, sizeof(Ptm));
        ret->pp = spp;
        ret->mtno = smt;
        ret->ov = ov;
        ret->kick_time = kick_time;
        ret->check_time = get_timing_dt(sld, rpgno, ridx);
        sld->check_timing[rmt][rpp]
            = list_append(sld->check_timing[rmt][rpp], ret);
    }
    if (time < 0) {
        int pidx = get_prev_timing_from_time(sld, spgno, rtime);
        recalc_scheduling_time_for_dt(sld, spgno, pidx);
    }
}
