nicvf_dump_intr_status(struct nicvf *nic)
{
	if (netif_msg_intr(nic))
		netdev_info(nic->netdev, "%s: interrupt status 0x%llx\n",
			    nic->netdev->name, nicvf_reg_read(nic, NIC_VF_INT));
}
