move_up() {
  int lineStartPos, column, prevLineStartPos, newPos, visLineNum;


  if ( position_to_line( mCursorPos, &visLineNum ) )
    lineStartPos = mLineStarts[ visLineNum ];
  else {
    lineStartPos = line_start( mCursorPos );
    visLineNum = -1;
  }
  if ( lineStartPos == 0 )
    return 0;


  column = mCursorPreferredCol >= 0 ? mCursorPreferredCol :
           mBuffer->count_displayed_characters( lineStartPos, mCursorPos );


  if ( visLineNum != -1 && visLineNum != 0 )
    prevLineStartPos = mLineStarts[ visLineNum - 1 ];
  else
    prevLineStartPos = rewind_lines( lineStartPos, 1 );
  newPos = mBuffer->skip_displayed_characters( prevLineStartPos, column );
  if (mContinuousWrap)
      newPos = min(newPos, line_end(prevLineStartPos, true));


  insert_position( newPos );


  mCursorPreferredCol = column;
  return 1;
}
