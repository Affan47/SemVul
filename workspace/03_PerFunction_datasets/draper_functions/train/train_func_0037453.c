sky2_put_idx(struct sky2_hw *hw, unsigned q, u16 idx)
{

	wmb();
	sky2_write16(hw, Y2_QADDR(q, PREF_UNIT_PUT_IDX), idx);
	DBGIO(PFX "queue %#x idx <- %d\n", q, idx);
}
