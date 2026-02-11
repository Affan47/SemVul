MarkRangeInserted(
	RecCursor *		pAfterCursor,
	void *			pEndOfRange)
{
	void *			pvField;

	for (pvField = pAfterCursor->Field();
		  pvField != pEndOfRange;
		  pvField = pAfterCursor->Field())
	{


		RecCursor::MarkInserted( pAfterCursor);
		pAfterCursor->Advance();
	}
}
