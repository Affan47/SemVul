nic_mbx_intr_handler (struct nicpf *nic, int mbx)
{
	u64 intr;
	u8  vf, vf_per_mbx_reg = 64;

	intr = nic_reg_read(nic, NIC_PF_MAILBOX_INT + (mbx << 3));
	dev_dbg(&nic->pdev->dev, "PF interrupt Mbox%d 0x%llx\n", mbx, intr);
	for (vf = 0; vf < vf_per_mbx_reg; vf++) {
		if (intr & (1ULL << vf)) {
			dev_dbg(&nic->pdev->dev, "Intr from VF %d\n",
				vf + (mbx * vf_per_mbx_reg));

			nic_handle_mbx_intr(nic, vf + (mbx * vf_per_mbx_reg));
			nic_clear_mbx_intr(nic, vf, mbx);
		}
	}
}
