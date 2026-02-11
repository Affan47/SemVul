setDirection(UT_BidiCharType dir, UT_BidiCharType dirOverride)
{
	if( !getLength()
		|| (   dir ==  static_cast<UT_BidiCharType>(UT_BIDI_UNSET)
			   && _getDirection() !=  static_cast<UT_BidiCharType>(UT_BIDI_UNSET)
		&& dirOverride == m_iDirOverride
		)
	  )
		return;

	UT_BidiCharType prevDir = m_iDirOverride ==  static_cast<UT_BidiCharType>(UT_BIDI_UNSET) ? _getDirection() : m_iDirOverride;
	if(dir ==  static_cast<UT_BidiCharType>(UT_BIDI_UNSET))
	{

		if(_getDirection() ==  static_cast<UT_BidiCharType>(UT_BIDI_UNSET))
		{


			PD_StruxIterator text(getBlock()->getStruxDocHandle(),
						  getBlockOffset() + fl_BLOCK_STRUX_OFFSET);

			text.setUpperLimit(text.getPosition() + getLength() - 1);

			UT_ASSERT_HARMLESS( text.getStatus() == UTIter_OK );

			UT_BidiCharType t = UT_BIDI_UNSET;

			while(text.getStatus() == UTIter_OK)
			{
				UT_UCS4Char c = text.getChar();

				t = UT_bidiGetCharType(c);

				if(UT_BIDI_IS_STRONG(t))
					break;

				++text;
			}

			_setDirection(t);
		}
	}
	else
	{
		_setDirection(dir);
	}

	if(dirOverride !=  static_cast<UT_BidiCharType>(UT_BIDI_IGNORE))
	{

		m_iDirOverride = dirOverride;


		if(dirOverride !=  static_cast<UT_BidiCharType>(UT_BIDI_UNSET))
			setVisDirection(dirOverride);
	}


	UT_BidiCharType curDir = m_iDirOverride ==  static_cast<UT_BidiCharType>(UT_BIDI_UNSET) ? _getDirection() : m_iDirOverride;

	UT_ASSERT(curDir !=  static_cast<UT_BidiCharType>(UT_BIDI_UNSET));

	if(curDir != prevDir)
	{

		clearScreen();
		markDrawBufferDirty();

		if(getLine())
		{
			getLine()->changeDirectionUsed(prevDir,curDir,true);

		}
	}
	else
	{
		if(!UT_BIDI_IS_STRONG(curDir) && getLine())
		{
			getLine()->setMapOfRunsDirty();
			clearScreen();
			markDrawBufferDirty();
		}
	}

}
