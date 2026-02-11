AscSetChipScsiID(PortAddr iop_base, uchar new_host_id)
{
	ushort cfg_lsw;

	if (AscGetChipScsiID(iop_base) == new_host_id) {
		return (new_host_id);
	}
	cfg_lsw = AscGetChipCfgLsw(iop_base);
	cfg_lsw &= 0xF8FF;
	cfg_lsw |= (ushort)((new_host_id & ASC_MAX_TID) << 8);
	AscSetChipCfgLsw(iop_base, cfg_lsw);
	return (AscGetChipScsiID(iop_base));
}
