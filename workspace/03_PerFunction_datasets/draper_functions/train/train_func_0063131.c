fore200e_close(struct atm_vcc* vcc)
{
    struct fore200e*        fore200e = FORE200E_DEV(vcc->dev);
    struct fore200e_vcc*    fore200e_vcc;
    struct fore200e_vc_map* vc_map;
    unsigned long           flags;

    ASSERT(vcc);
    ASSERT((vcc->vpi >= 0) && (vcc->vpi < 1<<FORE200E_VPI_BITS));
    ASSERT((vcc->vci >= 0) && (vcc->vci < 1<<FORE200E_VCI_BITS));

    DPRINTK(2, "closing %d.%d.%d:%d\n", vcc->itf, vcc->vpi, vcc->vci, fore200e_atm2fore_aal(vcc->qos.aal));

    clear_bit(ATM_VF_READY, &vcc->flags);

    fore200e_activate_vcin(fore200e, 0, vcc, 0);

    spin_lock_irqsave(&fore200e->q_lock, flags);

    vc_map = FORE200E_VC_MAP(fore200e, vcc->vpi, vcc->vci);


    vc_map->vcc = NULL;

    vcc->itf = vcc->vci = vcc->vpi = 0;

    fore200e_vcc = FORE200E_VCC(vcc);
    vcc->dev_data = NULL;

    spin_unlock_irqrestore(&fore200e->q_lock, flags);


    if ((vcc->qos.txtp.traffic_class == ATM_CBR) && (vcc->qos.txtp.max_pcr > 0)) {

	mutex_lock(&fore200e->rate_mtx);
	fore200e->available_cell_rate += vcc->qos.txtp.max_pcr;
	mutex_unlock(&fore200e->rate_mtx);

	clear_bit(ATM_VF_HASQOS, &vcc->flags);
    }

    clear_bit(ATM_VF_ADDR, &vcc->flags);
    clear_bit(ATM_VF_PARTIAL,&vcc->flags);

    ASSERT(fore200e_vcc);
    kfree(fore200e_vcc);
}
