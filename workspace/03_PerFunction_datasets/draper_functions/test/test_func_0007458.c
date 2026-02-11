measure_deleted_lines(int pos, int nDeleted) {
    int retPos, retLines, retLineStart, retLineEnd;
    Fl_Text_Buffer *buf = buffer();
    int nVisLines = mNVisibleLines;
    int *lineStarts = mLineStarts;
    int countFrom, lineStart;
    int nLines = 0, i;


    if (pos >= mFirstChar && pos <= mLastChar) {
    	for (i=nVisLines-1; i>0; i--)
    	    if (lineStarts[i] != -1 && pos >= lineStarts[i])
    		break;
    	if (i > 0) countFrom = lineStarts[i-1];
    	else countFrom = buf->line_start(pos);
    } else
    	countFrom = buf->line_start(pos);


    lineStart = countFrom;
    for (;;) {


    	wrapped_line_counter(buf, lineStart, buf->length(), 1, true, 0,
    	    	&retPos, &retLines, &retLineStart, &retLineEnd);
    	if (retPos >= buf->length()) {
    	    if (retPos != retLineEnd)
    	    	nLines++;
    	    break;
    	} else
    	    lineStart = retPos;
    	nLines++;
    	if (lineStart > pos + nDeleted &&
    	    	buf->character(lineStart-1) == '\n') {
    	    break;
    	}


    }
    mNLinesDeleted = nLines;
    mSuppressResync = 1;
}
