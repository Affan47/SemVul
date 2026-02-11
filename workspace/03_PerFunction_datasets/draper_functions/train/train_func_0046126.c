fiji_avfs_event_mgr(struct pp_smumgr *smumgr, bool smu_started)
{
	struct fiji_smumgr *priv = (struct fiji_smumgr *)(smumgr->backend);

	switch (priv->avfs.AvfsBtcStatus) {
	case AVFS_BTC_COMPLETED_SAVED:
		priv->avfs.AvfsBtcStatus = AVFS_BTC_RESTOREVFT_FAILED;
		PP_ASSERT_WITH_CODE(0 == fiji_restore_vft_table(smumgr),
				"[AVFS][fiji_avfs_event_mgr] Could not Copy Graphics "
				"Level table over to SMU",
				return -1;);
		priv->avfs.AvfsBtcStatus = AVFS_BTC_COMPLETED_RESTORED;
		break;
	case AVFS_BTC_COMPLETED_RESTORED:
		priv->avfs.AvfsBtcStatus = AVFS_BTC_SMUMSG_ERROR;
		PP_ASSERT_WITH_CODE(0 == fiji_send_msg_to_smc(smumgr,
				PPSMC_MSG_VftTableIsValid),
				"[AVFS][fiji_avfs_event_mgr] SMU did not respond "
				"correctly to VftTableIsValid Msg",
				return -1;);
		priv->avfs.AvfsBtcStatus = AVFS_BTC_SMUMSG_ERROR;
		PP_ASSERT_WITH_CODE(0 == fiji_send_msg_to_smc(smumgr,
				PPSMC_MSG_EnableAvfs),
				"[AVFS][fiji_avfs_event_mgr] SMU did not respond "
				"correctly to EnableAvfs Message Msg",
				return -1;);
		priv->avfs.AvfsBtcStatus = AVFS_BTC_COMPLETED_SAVED;
		break;
	case AVFS_BTC_BOOT:
		if (!smu_started)
			break;
		priv->avfs.AvfsBtcStatus = AVFS_BTC_FAILED;
		PP_ASSERT_WITH_CODE(0 == fiji_setup_pm_fuse_for_avfs(smumgr),
				"[AVFS][fiji_avfs_event_mgr] Failure at "
				"fiji_setup_pm_fuse_for_avfs",
				return -1;);
		priv->avfs.AvfsBtcStatus = AVFS_BTC_DPMTABLESETUP_FAILED;
		PP_ASSERT_WITH_CODE(0 == fiji_setup_graphics_level_structure(smumgr),
				"[AVFS][fiji_avfs_event_mgr] Could not Copy Graphics Level"
				" table over to SMU",
				return -1;);
		priv->avfs.AvfsBtcStatus = AVFS_BTC_VIRUS_FAIL;
		PP_ASSERT_WITH_CODE(0 == fiji_setup_pwr_virus(smumgr),
				"[AVFS][fiji_avfs_event_mgr] Could not setup "
				"Pwr Virus for AVFS ",
				return -1;);
		priv->avfs.AvfsBtcStatus = AVFS_BTC_FAILED;
		PP_ASSERT_WITH_CODE(0 == fiji_start_avfs_btc(smumgr),
				"[AVFS][fiji_avfs_event_mgr] Failure at "
				"fiji_start_avfs_btc. AVFS Disabled",
				return -1;);
		priv->avfs.AvfsBtcStatus = AVFS_BTC_SAVEVFT_FAILED;
		PP_ASSERT_WITH_CODE(0 == fiji_save_vft_table(smumgr),
				"[AVFS][fiji_avfs_event_mgr] Could not save VFT Table",
				return -1;);
		priv->avfs.AvfsBtcStatus = AVFS_BTC_COMPLETED_SAVED;
		break;
	case AVFS_BTC_DISABLED:
		break;
	case AVFS_BTC_NOTSUPPORTED:
		break;
	default:
		printk(KERN_ERR "[AVFS] Something is broken. See log!");
		break;
	}
	return 0;
}
