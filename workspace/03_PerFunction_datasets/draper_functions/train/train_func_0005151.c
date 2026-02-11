GetHashLeaves( CString tth )
{
	CByteArray * ba = 0;
	unsigned long hi = 0, hbi = 0;

	struct hashbaseobject * hbo = 0;
	CByteArray dst;

	if (CBase32::Decode(&dst, &tth) != dcpp::TigerTree::BYTES)
	{
		DPRINTF("GetHashLeaves: Decoded TTH length != dcpp::TigerTree::BYTES\n");
		return 0;
	}

	while ( FindHash(dst.Data(), &hi) )
	{


		if ( HashBaseIndexFromHashIndex( hi, &hbi ) )
		{

			hbo = (struct hashbaseobject *)(m_pHashBaseArray->Data()+hbi);

			if (hbo->m_nHashLeavesIndex == (unsigned long)-1)
			{
				DPRINTF("GetHashLeaves: No Leaves available.\n");
				return 0;
			}


			CFile leaffile;

			if ( leaffile.Open(CConfig::Instance()->GetConfigPath()+"hashleaves.bin", IO_RAW | IO_READONLY) == false )
			{
				printf("GetHashLeaves: cannot open hashleaves.bin\n");
				return 0;
			}

			ba = new CByteArray();

			if ( ReadLeaves( &leaffile, hbo->m_nHashLeavesIndex, ba ) == false )
			{
				printf("GetHashLeaves: hli=%lu tth=%s\n", hbo->m_nHashLeavesIndex, tth.Data());
				printf("GetHashLeaves: failed to read hash leaves, try database validation\n");
				delete ba;
				ba = 0;
			}

			leaffile.Close();

			return ba;
		}


		hi += dcpp::TigerTree::BYTES;
	}


	return 0;
}
