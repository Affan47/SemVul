SaveNewHashLeaves()
{
	bool res;

	if (m_pNewHashLeaves != 0)
	{

		CFile file;
		res = file.Open( CConfig::Instance()->GetConfigPath()+"hashleaves.bin",
			   IO_RAW | IO_WRITEONLY | IO_APPEND | IO_CREAT,
			   MO_IRUSR | MO_IWUSR
		);

		if ( res == false )
		{
			printf("CSearchIndex::SaveNewHashLeaves: open hashleaves.bin failed\n");
		}
		else
		{
			long wrote = file.Write( (const char*) m_pNewHashLeaves->Data(), m_pNewHashLeaves->Size() );

			if ( wrote == m_pNewHashLeaves->Size() )
			{
				res = true;
			}
			else
			{
				printf("CSearchIndex::SaveNewHashLeaves: only wrote %ld out of %ld bytes\n",wrote,m_pNewHashLeaves->Size());
				if ( wrote > 0 )
				{
					printf("CSearchIndex::SaveNewHashLeaves: hashleaves.bin has been corrupted, do /rebuild\n");
				}
				res = false;
			}

			file.Close();


			if ( wrote > 0 )
			{
				delete m_pNewHashLeaves;
				m_pNewHashLeaves = 0;
			}
		}
	}
	else
	{

		res = false;
	}

	return res;
}
