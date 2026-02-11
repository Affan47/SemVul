OutputCmap310Table(void * pCmapSubTblSrc, GrcBinaryStream * pbstrm,
	bool fFrom31)
{
	long lPosStart = pbstrm->Position();

	int cch = 0;


	pbstrm->WriteShort(12);


	pbstrm->WriteShort(0);


	int lPosLen = pbstrm->Position();
	pbstrm->WriteInt(0);


	pbstrm->WriteInt(0);


	int lPosNum = pbstrm->Position();
	pbstrm->WriteInt(0);


	unsigned int chLast = (fFrom31) ? 0xFFFF : 0x10FFFF;

	int key = 0;
	unsigned int ch = (fFrom31) ?
		TtfUtil::Cmap31NextCodepoint(pCmapSubTblSrc, 0, &key) :
		TtfUtil::Cmap310NextCodepoint(pCmapSubTblSrc, 0, &key);
	while (ch != chLast)
	{

		pbstrm->WriteInt(ch);

		pbstrm->WriteInt(ch);

		if (ch == kchwSpace)
			pbstrm->WriteInt(2);
		else
			pbstrm->WriteInt(0);

		cch++;

		ch = (fFrom31) ?
			TtfUtil::Cmap31NextCodepoint(pCmapSubTblSrc, ch, &key) :
			TtfUtil::Cmap310NextCodepoint(pCmapSubTblSrc, ch, &key);
	}

	int lPosEnd = pbstrm->Position();


	int cb = lPosEnd - lPosStart;
	pbstrm->SetPosition(lPosLen);
	pbstrm->WriteInt(cb);


	pbstrm->SetPosition(lPosNum);
	pbstrm->WriteInt(cch);

	pbstrm->SetPosition(lPosEnd);

	return cb;
}
