setMinId(idType t, UT_uint32 iMin)
{
	UT_return_val_if_fail(t < _Last, false);


	UT_return_val_if_fail(iMin < UINT_MAX - 1000, false);

	UT_uint32 i = (UT_uint32) t;

	if(m_iID[i] > iMin)
		return false;

	m_iID[i] = iMin;
	return true;
}
