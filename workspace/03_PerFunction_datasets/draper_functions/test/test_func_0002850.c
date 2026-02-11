Apply ( CSphString & sWord )
{
	if ( m_sCondition.IsEmpty () )
		return true;

	if ( sWord.IsEmpty () )
		return false;

	m_iWordLen = strlen ( sWord.cstr () );

	bool bDotCond = m_sCondition == ".";

	if ( m_eRule == RULE_SUFFIXES )
	{
		if ( ! bDotCond && ! CheckSuffix ( sWord ) )
			return false;

		if ( ! StripAppendSuffix ( sWord ) )
			return false;
	}
	else
	{
		if ( ! bDotCond && ! CheckPrefix ( sWord ) )
			return false;

		if ( ! StripAppendPrefix ( sWord ) )
			return false;
	}

	return true;
}
