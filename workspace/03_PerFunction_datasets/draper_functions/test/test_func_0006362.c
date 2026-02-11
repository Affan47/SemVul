isOneItem(fp_Run * pNext)
{
	GR_Itemization I;
	bool b = getBlock()->itemizeSpan(getBlockOffset(), getLength()+pNext->getLength(),I);
	UT_return_val_if_fail(b,false);
	if(I.getItemCount() <= 2)
	{


		PD_StruxIterator text(getBlock()->getStruxDocHandle(),
						  getBlockOffset() + fl_BLOCK_STRUX_OFFSET);

		text.setUpperLimit(text.getPosition() + getLength()+ pNext->getLength() - 1);
		UT_ASSERT_HARMLESS( text.getStatus() == UTIter_OK );
		bool bFoundRoman = false;
		bool bFoundUnicode = false;
		while(text.getStatus() == UTIter_OK)
	    {
			UT_UCS4Char c = text.getChar();
			if(c != ' ' && c <256)
			{
				bFoundRoman = true;
			}
			else if(c!= ' ' && !UT_isSmartQuotedCharacter(c))
			{
				bFoundUnicode = true;
			}
			++text;
		}
		if(bFoundRoman && bFoundUnicode)
		{
			return false;
		}
		return true;
	}
	return false;
}
