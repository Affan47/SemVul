insert_position( int newPos ) {

  if ( newPos == mCursorPos )
    return;
  if ( newPos < 0 ) newPos = 0;
  if ( newPos > mBuffer->length() ) newPos = mBuffer->length();


  mCursorPreferredCol = -1;


  redisplay_range(mCursorPos - 1, mCursorPos + 1);

  mCursorPos = newPos;


  redisplay_range(mCursorPos - 1, mCursorPos + 1);
}
