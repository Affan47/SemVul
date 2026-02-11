_cmicd_interrupt(bde_ctrl_t *ctrl)
{
    int d;
    int cmc = BDE_CMICD_PCIE_CMC;
    uint32 stat, mask = 0, fmask = 0, imask = 0;
    bde_inst_resource_t *res;

    d = (((uint8 *)ctrl - (uint8 *)_devices) / sizeof (bde_ctrl_t));
    res = &_bde_inst_resource[ctrl->inst];
    lkbde_irq_mask_get(d, &mask, &fmask);

    while (fmask) {
        stat = user_bde->read(d, CMIC_CMCx_IRQ_STAT0_OFFSET(cmc));
        imask = mask & ~fmask;
        if (stat & imask) {
            break;
        }
        stat = user_bde->read(d, CMIC_CMCx_IRQ_STAT1_OFFSET(cmc));
        mask = user_bde->read(d, CMIC_CMCx_PCIE_IRQ_MASK1_OFFSET(cmc));
        if (stat & mask) {
            break;
        }
        stat = user_bde->read(d, CMIC_CMCx_IRQ_STAT2_OFFSET(cmc));
        mask = user_bde->read(d, CMIC_CMCx_PCIE_IRQ_MASK2_OFFSET(cmc));
        if (stat & mask) {
            break;
        }
        stat = user_bde->read(d, CMIC_CMCx_IRQ_STAT3_OFFSET(cmc));
        mask = user_bde->read(d, CMIC_CMCx_PCIE_IRQ_MASK3_OFFSET(cmc));
        if (stat & mask) {
            break;
        }
        stat = user_bde->read(d, CMIC_CMCx_IRQ_STAT4_OFFSET(cmc));
        mask = user_bde->read(d, CMIC_CMCx_PCIE_IRQ_MASK4_OFFSET(cmc));
        if (stat & mask) {
            break;
        }
        stat = user_bde->read(d, CMIC_CMCx_IRQ_STAT5_OFFSET(cmc));
        mask = user_bde->read(d, CMIC_CMCx_PCIE_IRQ_MASK5_OFFSET(cmc));
        if (stat & mask) {
            break;
        }
        stat = user_bde->read(d, CMIC_CMCx_IRQ_STAT6_OFFSET(cmc));
        mask = user_bde->read(d, CMIC_CMCx_PCIE_IRQ_MASK6_OFFSET(cmc));
        if (stat & mask) {
            break;
        }
        return;
    }

    lkbde_irq_mask_set(d, CMIC_CMCx_PCIE_IRQ_MASK0_OFFSET(cmc), 0, 0);
    user_bde->write(d, CMIC_CMCx_PCIE_IRQ_MASK1_OFFSET(cmc), 0);
    user_bde->write(d, CMIC_CMCx_PCIE_IRQ_MASK2_OFFSET(cmc), 0);
    user_bde->write(d, CMIC_CMCx_PCIE_IRQ_MASK3_OFFSET(cmc), 0);
    user_bde->write(d, CMIC_CMCx_PCIE_IRQ_MASK4_OFFSET(cmc), 0);
    user_bde->write(d, CMIC_CMCx_PCIE_IRQ_MASK5_OFFSET(cmc), 0);
    user_bde->write(d, CMIC_CMCx_PCIE_IRQ_MASK6_OFFSET(cmc), 0);

    atomic_set(&res->intr, 1);
#ifdef BDE_LINUX_NON_INTERRUPTIBLE
    wake_up(&res->intr_wq);
#else
    wake_up_interruptible(&res->intr_wq);
#endif
}
