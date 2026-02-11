set_fv_cost_by_sb_body_param(Ctrl_task *ctrl_task, Ctrl_task *sc)
{
    real fv_p_cost, energy;
    fv_kind fv;

    for (fv = FULL; fv <= LAST_FV; fv++) {
        if (sc->fv_mask[fv]) {
            real fv_cost;
            fv_cost = ctrl_task_get_fv_cost(sc, fv);
            ctrl_task_set_fv_cost(ctrl_task, fv, fv_cost);
            ctrl_task_set_fv_mask(ctrl_task, fv, TRUE);
        }
    }

    fv_p_cost = ctrl_task_get_fv_p_cost(sc);
    ctrl_task_set_fv_p_cost(ctrl_task, fv_p_cost);

    energy = ctrl_task_get_energy(sc);
    ctrl_task_set_energy(ctrl_task, energy);
}
