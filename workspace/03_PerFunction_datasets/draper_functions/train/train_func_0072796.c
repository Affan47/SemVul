bgx_lmac_disable(struct bgx *bgx, u8 lmacid)
{
	struct lmac *lmac;
	u64 cfg;

	lmac = &bgx->lmac[lmacid];
	if (lmac->check_link) {

		cancel_delayed_work_sync(&lmac->dwork);
		destroy_workqueue(lmac->check_link);
	}


	cfg = bgx_reg_read(bgx, lmacid, BGX_CMRX_CFG);
	cfg &= ~CMR_PKT_RX_EN;
	bgx_reg_write(bgx, lmacid, BGX_CMRX_CFG, cfg);


	bgx_poll_reg(bgx, lmacid, BGX_CMRX_RX_FIFO_LEN, (u64)0x1FFF, true);
	bgx_poll_reg(bgx, lmacid, BGX_CMRX_TX_FIFO_LEN, (u64)0x3FFF, true);


	cfg = bgx_reg_read(bgx, lmacid, BGX_CMRX_CFG);
	cfg &= ~CMR_PKT_TX_EN;
	bgx_reg_write(bgx, lmacid, BGX_CMRX_CFG, cfg);


        if (!lmac->is_sgmii)
                bgx_reg_modify(bgx, lmacid,
                               BGX_SPUX_CONTROL1, SPU_CTL_LOW_POWER);
        else
                bgx_reg_modify(bgx, lmacid,
                               BGX_GMP_PCS_MRX_CTL, PCS_MRX_CTL_PWR_DN);


	cfg = bgx_reg_read(bgx, lmacid, BGX_CMRX_CFG);
	cfg &= ~CMR_EN;
	bgx_reg_write(bgx, lmacid, BGX_CMRX_CFG, cfg);

	bgx_flush_dmac_addrs(bgx, lmacid);

	if ((bgx->lmac_type != BGX_MODE_XFI) &&
	    (bgx->lmac_type != BGX_MODE_XLAUI) &&
	    (bgx->lmac_type != BGX_MODE_40G_KR) &&
	    (bgx->lmac_type != BGX_MODE_10G_KR) && lmac->phydev)
		phy_disconnect(lmac->phydev);

	lmac->phydev = NULL;
}
