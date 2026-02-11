shbde_iproc_pcie_preemphasis_set(shbde_hal_t *shbde, void *iproc_regs,
                                 shbde_iproc_config_t *icfg, void *pci_dev)
{
    shbde_mdio_ctrl_t mdio_ctrl, *smc = &mdio_ctrl;
    unsigned int phy_addr, data;
    void *reg;
    unsigned int pcie_cap_base;
    unsigned short link_stat, link_stat2;

    if (!icfg) {
        return -1;
    }


    phy_addr = icfg->pcie_phy_addr;
    if (phy_addr == 0 || icfg->mdio_base_addr == 0) {
        return 0;
    }


    smc->shbde = shbde;
    smc->regs = iproc_regs;
    smc->base_addr = icfg->mdio_base_addr;
    smc->io32_read = shbde_iproc_pci_read;
    smc->io32_write = shbde_iproc_pci_write;
    shbde_iproc_mdio_init(smc);


    shbde_iproc_mdio_write(smc, phy_addr, 0x1f, 0x8630);
    shbde_iproc_mdio_write(smc, phy_addr, 0x13, 0x190);
    shbde_iproc_mdio_write(smc, phy_addr, 0x19, 0x191);

    if (!icfg->adjust_pcie_preemphasis) {
        return 0;
    }


    if (!shbde || !shbde->pcic16_read || !pci_dev) {
        return -1;
    }
    pcie_cap_base = shbde_pci_pcie_cap(shbde, pci_dev);
    if (pcie_cap_base) {
        link_stat = shbde->pcic16_read(pci_dev,
                                       pcie_cap_base + PCI_EXP_LNKSTA);
        link_stat2 = shbde->pcic16_read(pci_dev,
                                        pcie_cap_base + PCI_EXP_LNKSTA2);
        if (((link_stat & 0xf) == PCI_EXP_LNKSTA_CLS_5_0GB) &&
            (link_stat2 & PCI_EXP_LNKSTA2_CDL_3_5DB)) {


            shbde_iproc_mdio_write(smc, phy_addr, 0x1f, 0x8610);
            shbde_iproc_mdio_read(smc, phy_addr, 0x17, &data);
            data &= ~0xf00;
            data |= 0x700;
            shbde_iproc_mdio_write(smc, phy_addr, 0x17, data);


            data = 0;
            REG_FIELD_SET(PAXB_CONFIG_IND_ADDRr, PROTOCOL_LAYERf, data, 0x2);
            REG_FIELD_SET(PAXB_CONFIG_IND_ADDRr, ADDRESSf, data, 0x4);
            reg = ROFFS(iproc_regs, BAR0_PAXB_CONFIG_IND_ADDR);
            iproc32_write(shbde, reg, data);

            reg = ROFFS(iproc_regs, BAR0_PAXB_CONFIG_IND_DATA);
            data = iproc32_read(shbde, reg);
            data &= ~0x4000;
            iproc32_write(shbde, reg, data);
            data |= 0x4000;
            iproc32_write(shbde, reg, data);
            data &= ~0x4000;
            iproc32_write(shbde, reg, data);


            wait_usec(shbde, 1000);
        }
    }

    return 0;
}
