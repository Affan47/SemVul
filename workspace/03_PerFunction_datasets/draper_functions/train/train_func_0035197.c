rio_clear_locks(struct rio_net *net)
{
	struct rio_mport *port = net->hport;
	struct rio_dev *rdev;
	u32 result;
	int ret = 0;


	rio_local_write_config_32(port, RIO_HOST_DID_LOCK_CSR,
				  port->host_deviceid);
	rio_local_read_config_32(port, RIO_HOST_DID_LOCK_CSR, &result);
	if ((result & 0xffff) != 0xffff) {
		printk(KERN_INFO
		       "RIO: badness when releasing host lock on master port, result %8.8x\n",
		       result);
		ret = -EINVAL;
	}
	list_for_each_entry(rdev, &net->devices, net_list) {
		rio_write_config_32(rdev, RIO_HOST_DID_LOCK_CSR,
				    port->host_deviceid);
		rio_read_config_32(rdev, RIO_HOST_DID_LOCK_CSR, &result);
		if ((result & 0xffff) != 0xffff) {
			printk(KERN_INFO
			       "RIO: badness when releasing host lock on vid %4.4x did %4.4x\n",
			       rdev->vid, rdev->did);
			ret = -EINVAL;
		}


		rio_read_config_32(rdev,
				   rdev->phys_efptr + RIO_PORT_GEN_CTL_CSR,
				   &result);
		result |= RIO_PORT_GEN_DISCOVERED | RIO_PORT_GEN_MASTER;
		rio_write_config_32(rdev,
				    rdev->phys_efptr + RIO_PORT_GEN_CTL_CSR,
				    result);
	}

	return ret;
}
