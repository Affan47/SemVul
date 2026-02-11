tach2rpm(u16 tach)
{
	if (tach == 0 || tach == 0xFFFF)
		return 0;

	return (90000 * 60) / tach;
}
