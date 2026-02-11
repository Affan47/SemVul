gs_setoverprint(gs_state * pgs, bool ovp)
{
    bool    prior_ovp = pgs->overprint;
    cmm_dev_profile_t *profile_struct;
    gx_device *dev = pgs->device;


    if (dev != NULL) {
        if (dev->procs.get_profile == NULL) {
            profile_struct = dev->icc_struct;
        } else {
            dev_proc(dev, get_profile)(dev,  &profile_struct);
        }
        if (profile_struct->sim_overprint == false) return;
    }
    pgs->overprint = ovp;
    if (prior_ovp != ovp)
        (void)gs_do_set_overprint(pgs);
}
