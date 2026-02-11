GetReport()
{
	CTreeVerificationReport * pointer = 0;

	if ( GetStatus() == efhsFinished )
	{
		pointer = m_pReport;
		m_pReport = 0;
	}

	return pointer;
}
