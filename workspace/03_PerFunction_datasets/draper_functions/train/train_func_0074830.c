CreateQLutLossless(LONG cbit)
{
	JlsCustomParameters preset = ComputeDefault((1 << cbit) - 1, 0);
	LONG range = preset.MAXVAL + 1;

	std::vector<signed char> lut(range * 2);

	for (LONG diff = -range; diff < range; diff++)
	{
		lut[range + diff] = QuantizeGratientOrg(preset, 0,diff);
	}
	return lut;
}
