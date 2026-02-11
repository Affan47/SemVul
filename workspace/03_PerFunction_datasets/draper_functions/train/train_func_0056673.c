flexcop_dma_remap(struct flexcop_device *fc,
		flexcop_dma_index_t dma_idx,
		int onoff)
{
	flexcop_ibi_register r = (dma_idx & FC_DMA_1) ? dma1_00c : dma2_01c;
	flexcop_ibi_value v = fc->read_ibi_reg(fc,r);
	deb_info("%s\n",__func__);
	v.dma_0xc.remap_enable = onoff;
	fc->write_ibi_reg(fc,r,v);
	return 0;
}
