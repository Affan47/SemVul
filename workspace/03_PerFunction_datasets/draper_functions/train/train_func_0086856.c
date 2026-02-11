frametype(u32 rspec, u8 mimoframe)
{
	if (is_mcs_rate(rspec))
		return mimoframe;
	return is_cck_rate(rspec) ? FT_CCK : FT_OFDM;
}
