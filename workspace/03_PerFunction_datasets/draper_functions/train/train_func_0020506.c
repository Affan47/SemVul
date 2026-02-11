adpt_abort(struct scsi_cmnd * cmd)
{
	adpt_hba* pHba = NULL;
	struct adpt_device* dptdevice;
	u32 msg[5];
	int rcode;

	if(cmd->serial_number == 0){
		return FAILED;
	}
	pHba = (adpt_hba*) cmd->device->host->hostdata[0];
	printk(KERN_INFO"%s: Trying to Abort\n",pHba->name);
	if ((dptdevice = (void*) (cmd->device->hostdata)) == NULL) {
		printk(KERN_ERR "%s: Unable to abort: No device in cmnd\n",pHba->name);
		return FAILED;
	}

	memset(msg, 0, sizeof(msg));
	msg[0] = FIVE_WORD_MSG_SIZE|SGL_OFFSET_0;
	msg[1] = I2O_CMD_SCSI_ABORT<<24|HOST_TID<<12|dptdevice->tid;
	msg[2] = 0;
	msg[3]= 0;
	msg[4] = adpt_cmd_to_context(cmd);
	if (pHba->host)
		spin_lock_irq(pHba->host->host_lock);
	rcode = adpt_i2o_post_wait(pHba, msg, sizeof(msg), FOREVER);
	if (pHba->host)
		spin_unlock_irq(pHba->host->host_lock);
	if (rcode != 0) {
		if(rcode == -EOPNOTSUPP ){
			printk(KERN_INFO"%s: Abort cmd not supported\n",pHba->name);
			return FAILED;
		}
		printk(KERN_INFO"%s: Abort failed.\n",pHba->name);
		return FAILED;
	}
	printk(KERN_INFO"%s: Abort complete.\n",pHba->name);
	return SUCCESS;
}
