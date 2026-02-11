handleLineDown(uint sysKeys)
{
	size_t caratLine = getLineNumberFromIndex(d_caratPos);

	if ((d_lines.size() > 1) && (caratLine < (d_lines.size() - 1)))
	{
        float caratPixelOffset = getFont()->getTextExtent(getText().substr(d_lines[caratLine].d_startIdx, d_caratPos - d_lines[caratLine].d_startIdx));

		++caratLine;

        size_t newLineIndex = getFont()->getCharAtPixel(getText().substr(d_lines[caratLine].d_startIdx, d_lines[caratLine].d_length), caratPixelOffset);

		setCaratIndex(d_lines[caratLine].d_startIdx + newLineIndex);
	}

	if (sysKeys & Shift)
	{
		setSelection(d_caratPos, d_dragAnchorIdx);
	}
	else
	{
		clearSelection();
	}

}
