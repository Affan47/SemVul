Distance (double dx, double dy, double dz, bool bFixed)
{
	if ((m_nCleave > 0) && ! bFixed) return 0. ;
	dx -= x() ;
	dy -= y() ;
	dz -= z() ;
	return sqrt(dx * dx + dy * dy + dz * dz) + m_Radius.value.value ;
}
