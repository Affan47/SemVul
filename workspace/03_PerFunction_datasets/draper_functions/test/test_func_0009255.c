_addPropertyItem (tControl index, const sControlData & control_data)
{
	sControlData * pDataCopy = 0;

	try
		{
			pDataCopy = new sControlData(control_data);
		}
	catch(...)
		{
			pDataCopy = 0;
		}
	UT_return_if_fail (pDataCopy);

	m_vecProperties.setNthItem (static_cast<UT_uint32>(index), pDataCopy, 0);
}
