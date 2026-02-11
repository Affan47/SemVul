phy_length(const struct skge_hw *hw, u32 status)
{
	if (is_genesis(hw))
		return status >> XMR_FS_LEN_SHIFT;
	else
		return status >> GMR_FS_LEN_SHIFT;
}
