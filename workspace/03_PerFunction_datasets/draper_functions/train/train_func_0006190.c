lio_cn6xxx_setup_iq_regs(struct octeon_device *oct, u32 iq_no)
{
	struct octeon_instr_queue *iq = oct->instr_queue[iq_no];


	octeon_write_csr64(oct, CN6XXX_SLI_IQ_PKT_INSTR_HDR64(iq_no), 0);


	octeon_write_csr64(oct, CN6XXX_SLI_IQ_BASE_ADDR64(iq_no),
			   iq->base_addr_dma);
	octeon_write_csr(oct, CN6XXX_SLI_IQ_SIZE(iq_no), iq->max_count);


	iq->doorbell_reg = oct->mmio[0].hw_addr + CN6XXX_SLI_IQ_DOORBELL(iq_no);
	iq->inst_cnt_reg = oct->mmio[0].hw_addr
			   + CN6XXX_SLI_IQ_INSTR_COUNT(iq_no);
	dev_dbg(&oct->pci_dev->dev, "InstQ[%d]:dbell reg @ 0x%p instcnt_reg @ 0x%p\n",
		iq_no, iq->doorbell_reg, iq->inst_cnt_reg);


	iq->reset_instr_cnt = readl(iq->inst_cnt_reg);
}
