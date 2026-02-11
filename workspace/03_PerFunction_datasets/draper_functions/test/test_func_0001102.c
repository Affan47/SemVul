pm8001_mpi_reg_resp(struct pm8001_hba_info *pm8001_ha, void *piomb)
{
	u32 status;
	u32 device_id;
	u32 htag;
	struct pm8001_ccb_info *ccb;
	struct pm8001_device *pm8001_dev;
	struct dev_reg_resp *registerRespPayload =
		(struct dev_reg_resp *)(piomb + 4);

	htag = le32_to_cpu(registerRespPayload->tag);
	ccb = &pm8001_ha->ccb_info[htag];
	pm8001_dev = ccb->device;
	status = le32_to_cpu(registerRespPayload->status);
	device_id = le32_to_cpu(registerRespPayload->device_id);
	PM8001_MSG_DBG(pm8001_ha,
		pm8001_printk(" register device is status = %d\n", status));
	switch (status) {
	case DEVREG_SUCCESS:
		PM8001_MSG_DBG(pm8001_ha, pm8001_printk("DEVREG_SUCCESS\n"));
		pm8001_dev->device_id = device_id;
		break;
	case DEVREG_FAILURE_OUT_OF_RESOURCE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("DEVREG_FAILURE_OUT_OF_RESOURCE\n"));
		break;
	case DEVREG_FAILURE_DEVICE_ALREADY_REGISTERED:
		PM8001_MSG_DBG(pm8001_ha,
		   pm8001_printk("DEVREG_FAILURE_DEVICE_ALREADY_REGISTERED\n"));
		break;
	case DEVREG_FAILURE_INVALID_PHY_ID:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("DEVREG_FAILURE_INVALID_PHY_ID\n"));
		break;
	case DEVREG_FAILURE_PHY_ID_ALREADY_REGISTERED:
		PM8001_MSG_DBG(pm8001_ha,
		   pm8001_printk("DEVREG_FAILURE_PHY_ID_ALREADY_REGISTERED\n"));
		break;
	case DEVREG_FAILURE_PORT_ID_OUT_OF_RANGE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("DEVREG_FAILURE_PORT_ID_OUT_OF_RANGE\n"));
		break;
	case DEVREG_FAILURE_PORT_NOT_VALID_STATE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("DEVREG_FAILURE_PORT_NOT_VALID_STATE\n"));
		break;
	case DEVREG_FAILURE_DEVICE_TYPE_NOT_VALID:
		PM8001_MSG_DBG(pm8001_ha,
		       pm8001_printk("DEVREG_FAILURE_DEVICE_TYPE_NOT_VALID\n"));
		break;
	default:
		PM8001_MSG_DBG(pm8001_ha,
		 pm8001_printk("DEVREG_FAILURE_DEVICE_TYPE_NOT_UNSORPORTED\n"));
		break;
	}
	complete(pm8001_dev->dcompletion);
	ccb->task = NULL;
	ccb->ccb_tag = 0xFFFFFFFF;
	pm8001_tag_free(pm8001_ha, htag);
	return 0;
}
