ipmi_heartbeat(void)
{
	struct kernel_ipmi_msg            msg;
	int                               rv;
	struct ipmi_system_interface_addr addr;
	int				  timeout_retries = 0;

	if (ipmi_ignore_heartbeat)
		return 0;

	if (ipmi_start_timer_on_heartbeat) {
		ipmi_start_timer_on_heartbeat = 0;
		ipmi_watchdog_state = action_val;
		return ipmi_set_timeout(IPMI_SET_TIMEOUT_FORCE_HB);
	} else if (pretimeout_since_last_heartbeat) {


		return ipmi_set_timeout(IPMI_SET_TIMEOUT_HB_IF_NECESSARY);
	}

	mutex_lock(&heartbeat_lock);

restart:
	atomic_set(&heartbeat_tofree, 2);


	if (ipmi_watchdog_state == WDOG_TIMEOUT_NONE) {
		mutex_unlock(&heartbeat_lock);
		return 0;
	}

	addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	addr.channel = IPMI_BMC_CHANNEL;
	addr.lun = 0;

	msg.netfn = 0x06;
	msg.cmd = IPMI_WDOG_RESET_TIMER;
	msg.data = NULL;
	msg.data_len = 0;
	rv = ipmi_request_supply_msgs(watchdog_user,
				      (struct ipmi_addr *) &addr,
				      0,
				      &msg,
				      NULL,
				      &heartbeat_smi_msg,
				      &heartbeat_recv_msg,
				      1);
	if (rv) {
		mutex_unlock(&heartbeat_lock);
		printk(KERN_WARNING PFX "heartbeat failure: %d\n",
		       rv);
		return rv;
	}


	wait_for_completion(&heartbeat_wait);

	if (heartbeat_recv_msg.msg.data[0] == IPMI_WDOG_TIMER_NOT_INIT_RESP)  {
		timeout_retries++;
		if (timeout_retries > 3) {
			printk(KERN_ERR PFX ": Unable to restore the IPMI"
			       " watchdog's settings, giving up.\n");
			rv = -EIO;
			goto out_unlock;
		}


		rv = ipmi_set_timeout(IPMI_SET_TIMEOUT_NO_HB);
		if (rv) {
			printk(KERN_ERR PFX ": Unable to send the command to"
			       " set the watchdog's settings, giving up.\n");
			goto out_unlock;
		}


		goto restart;
	} else if (heartbeat_recv_msg.msg.data[0] != 0) {


		rv = -EINVAL;
	}

out_unlock:
	mutex_unlock(&heartbeat_lock);

	return rv;
}
