calc_line_starts( int startLine, int endLine ) {
  int startPos, bufLen = mBuffer->length();
  int line, lineEnd, nextLineStart, nVis = mNVisibleLines;
  int *lineStarts = mLineStarts;


  if ( endLine < 0 ) endLine = 0;
  if ( endLine >= nVis ) endLine = nVis - 1;
  if ( startLine < 0 ) startLine = 0;
  if ( startLine >= nVis ) startLine = nVis - 1;
  if ( startLine > endLine )
    return;


  if ( startLine == 0 ) {
    lineStarts[ 0 ] = mFirstChar;
    startLine = 1;
  }
  startPos = lineStarts[ startLine - 1 ];


  if ( startPos == -1 ) {
    for ( line = startLine; line <= endLine; line++ )
      lineStarts[ line ] = -1;
    return;
  }


  for ( line = startLine; line <= endLine; line++ ) {
    find_line_end(startPos, true, &lineEnd, &nextLineStart);
    startPos = nextLineStart;
    if ( startPos >= bufLen ) {


      if ( line == 0 || ( lineStarts[ line - 1 ] != bufLen &&
                         lineEnd != nextLineStart ) ) {
        lineStarts[ line ] = bufLen;
        line++;
      }
      break;
    }
    lineStarts[ line ] = startPos;
  }


  for ( ; line <= endLine; line++ )
    lineStarts[ line ] = -1;
}
