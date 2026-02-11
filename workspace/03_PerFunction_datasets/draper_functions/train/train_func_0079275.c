begin_composite(i_ctx_t *i_ctx_p, alpha_composite_state_t * pcp)
{
    gx_device *dev = gs_currentdevice(igs);
    int code =
        gs_create_composite_alpha(&pcp->pcte, &pcp->params, imemory);

    if (code < 0)
        return code;
    pcp->orig_dev = pcp->cdev = dev;
    code = (*dev_proc(dev, create_compositor))
        (dev, &pcp->cdev, pcp->pcte, (gs_imager_state *)igs, imemory, NULL);
    if (code < 0) {
        end_composite(i_ctx_p, pcp);
        return code;
    }
    gs_setdevice_no_init(igs, pcp->cdev);
    return 0;
}
