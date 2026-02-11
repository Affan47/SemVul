intel_gen(uint32_t devid)
{
	if (IS_GEN2(devid))
		return 2;
	if (IS_GEN3(devid))
		return 3;
	if (IS_GEN4(devid))
		return 4;
	if (IS_GEN5(devid))
		return 5;
	if (IS_GEN6(devid))
		return 6;
	if (IS_GEN7(devid))
		return 7;

	return -1;
}
