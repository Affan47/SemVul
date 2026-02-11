brcms_b_read_objmem(struct brcms_hardware *wlc_hw, uint offset, u32 sel)
{
	struct bcma_device *core = wlc_hw->d11core;
	u16 objoff = D11REGOFFS(objdata);

	bcma_write32(core, D11REGOFFS(objaddr), sel | (offset >> 2));
	(void)bcma_read32(core, D11REGOFFS(objaddr));
	if (offset & 2)
		objoff += 2;

	return bcma_read16(core, objoff);
}
