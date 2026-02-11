flexcop_reset_block_300(struct flexcop_device *fc)
{
	flexcop_ibi_value v208_save = fc->read_ibi_reg(fc, ctrl_208),
			  v210 = fc->read_ibi_reg(fc, sw_reset_210);

	deb_rdump("208: %08x, 210: %08x\n", v208_save.raw, v210.raw);
	fc->write_ibi_reg(fc,ctrl_208,ibi_zero);

	v210.sw_reset_210.reset_block_300 = 1;
	v210.sw_reset_210.Block_reset_enable = 0xb2;

	fc->write_ibi_reg(fc,sw_reset_210,v210);
	fc->write_ibi_reg(fc,ctrl_208,v208_save);
}
