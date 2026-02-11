_appendBlock(AP_Preview_Paragraph_Block * block)
{
	UT_return_if_fail (block);

	UT_uint32 ypre = 0;
	UT_uint32 ypost = 0;

	UT_sint32 wordCounter = 0;
	UT_sint32 wordCount = block->m_words.getItemCount();

	m_gc->setColor(block->m_clr);

	{


		switch (block->m_spacing)
		{
		case AP_Dialog_Paragraph::spacing_UNDEF:
		case AP_Dialog_Paragraph::spacing_SINGLE:
		case AP_Dialog_Paragraph::spacing_ONEANDHALF:
		case AP_Dialog_Paragraph::spacing_DOUBLE:
		case AP_Dialog_Paragraph::spacing_MULTIPLE:
			ypost = block->m_lineSpacing;
			break;
		case AP_Dialog_Paragraph::spacing_ATLEAST:
		case AP_Dialog_Paragraph::spacing_EXACTLY:
			ypre = block->m_lineSpacing;
			break;
		default:
			UT_ASSERT_HARMLESS(UT_SHOULD_NOT_HAPPEN);
		}
	}


	UT_uint32 y = m_y;


	y += block->m_beforeSpacing;


	y += ypre;

	wordCounter += _appendLine(&block->m_words,
							   &block->m_widths,
							   0,
							   block->m_firstLineLeftStop,
							   block->m_rightStop,
							   block->m_align,
							   y);
	y += block->m_fontHeight;

	y += ypost;


	UT_uint32 newWords = 1;
	while (wordCounter < wordCount && newWords > 0)
	{

		y += ypre;

		newWords = _appendLine(&block->m_words,
					      	   &block->m_widths,
							   wordCounter,
							   block->m_leftStop,
							   block->m_rightStop,
							   block->m_align,
							   y);

		wordCounter += newWords;

		y += block->m_fontHeight;

		y += ypost;
	}


	y += block->m_afterSpacing;


	m_y = y;
}
