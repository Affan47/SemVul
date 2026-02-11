gx_end_transparency_mask(gs_imager_state * pis, gx_device * pdev,
                                const gs_pdf14trans_params_t * pparams)
{
    if_debug2m('v', pis->memory,
               "[v](0x%lx)gx_end_transparency_mask(%d)\n", (ulong)pis,
               (int)pparams->csel);
    if (dev_proc(pdev, end_transparency_mask) != 0)
        return (*dev_proc(pdev, end_transparency_mask)) (pdev, pis);
    else
        return 0;
}
