draw_text( int left, int top, int width, int height ) {
  int fontHeight, firstLine, lastLine, line;


  fontHeight = mMaxsize ? mMaxsize : textsize_;
  firstLine = ( top - text_area.y - fontHeight + 1 ) / fontHeight;
  lastLine = ( top + height - text_area.y ) / fontHeight + 1;

  fl_push_clip( left, top, width, height );


  for ( line = firstLine; line <= lastLine; line++ )
    draw_vline( line, left, left + width, 0, INT_MAX );


  if (mLineNumWidth != 0 && left <= mLineNumLeft + mLineNumWidth)
    draw_line_numbers(false);

  fl_pop_clip();
}
