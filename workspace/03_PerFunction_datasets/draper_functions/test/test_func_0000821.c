set_bb_reg(struct _adapter *pAdapter,
		     u16 offset,
		     u32 bitmask,
		     u32 value)
{
	u32 org_value, bit_shift, new_value;

	if (bitmask != bMaskDWord) {
		org_value = r8712_bb_reg_read(pAdapter, offset);
		bit_shift = bitshift(bitmask);
		new_value = ((org_value & (~bitmask)) | (value << bit_shift));
	} else {
		new_value = value;
	}
	return r8712_bb_reg_write(pAdapter, offset, new_value);
}
