qla2x00_restart_timer(scsi_qla_host_t *vha, unsigned long interval)
{

	if (vha->device_flags & DFLG_DEV_FAILED) {
		ql_dbg(ql_dbg_timer, vha, 0x600d,
		    "Device in a failed state, returning.\n");
		return;
	}

	mod_timer(&vha->timer, jiffies + interval * HZ);
}
