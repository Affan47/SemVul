OutputFeatTable(GrcBinaryStream * pbstrm, long lTableStart,
	int fxdVersion)
{
	std::vector<int> vnOffsets;
	std::vector<long> vlOffsetPos;


	pbstrm->WriteShort(m_vpfeat.size());


	pbstrm->WriteShort(0);
	pbstrm->WriteInt(0);

	size_t ifeat;
	for (ifeat = 0; ifeat < m_vpfeat.size(); ifeat++)
	{

		if (fxdVersion >= 0x00020000)
			pbstrm->WriteInt(m_vpfeat[ifeat]->ID());
		else
			pbstrm->WriteShort(m_vpfeat[ifeat]->ID());


		pbstrm->WriteShort(m_vpfeat[ifeat]->NumberOfSettings());

		if (fxdVersion >= 0x00020000)
			pbstrm->WriteShort(0);


		vlOffsetPos.push_back(pbstrm->Position());
		pbstrm->WriteInt(0);


		pbstrm->WriteShort(0x8000);


		pbstrm->WriteShort(m_vpfeat[ifeat]->NameTblId());
	}

	for (ifeat = 0; ifeat < m_vpfeat.size(); ifeat++)
	{
		vnOffsets.push_back(pbstrm->Position() - lTableStart);
		m_vpfeat[ifeat]->OutputSettings(pbstrm);
	}

	Assert(vnOffsets.size() == m_vpfeat.size());


	long lSavePos = pbstrm->Position();

	for (ifeat = 0; ifeat < vnOffsets.size(); ifeat++)
	{
		pbstrm->SetPosition(vlOffsetPos[ifeat]);
		pbstrm->WriteInt(vnOffsets[ifeat]);
	}

	pbstrm->SetPosition(lSavePos);
}
