shbde_iproc_mdio_init(shbde_mdio_ctrl_t *smc)
{
    shbde_hal_t *shbde = smc->shbde;
    unsigned int reg_val = 0;


    REG_FIELD_SET(MII_MGMT_CTRLr, MDCDIVf, reg_val, 0x7f);
    mdio32_write(smc, MII_MGMT_CTRL, reg_val);

    if (shbde && !shbde->usleep) {
        LOG_DBG(shbde, "shbde_mdio: no registration of usleep vector", 0);
    }

    wait_usec(smc, 100);

    return 0;
}
