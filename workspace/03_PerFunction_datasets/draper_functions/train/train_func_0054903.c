clearScreen(GR_Graphics* ) const
{
	fp_Line* pLine = static_cast<fp_Line *>(getFirstContainer());
	if(isHdrFtr())
	{
		return;
	}
	while (pLine)
	{


		if(!pLine->isEmpty())
			pLine->clearScreen();
		pLine = static_cast<fp_Line *>(pLine->getNext());
	}
}
