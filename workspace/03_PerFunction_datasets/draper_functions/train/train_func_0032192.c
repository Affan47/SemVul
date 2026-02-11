igb_vmdq_set_replication_pf(struct e1000_hw *hw, bool enable)
{
	u32 vt_ctl = rd32(E1000_VT_CTL);

	if (enable)
		vt_ctl |= E1000_VT_CTL_VM_REPL_EN;
	else
		vt_ctl &= ~E1000_VT_CTL_VM_REPL_EN;

	wr32(E1000_VT_CTL, vt_ctl);
}
