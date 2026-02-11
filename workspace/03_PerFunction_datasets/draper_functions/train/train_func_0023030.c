drawTextRegion( QPainter& paint, const QString& text,
				int row_start, int row_stop,
				int col_start, int col_stop )
{
  paint.setPen(qApp->palette().foreground().color());
  for(int r = row_start; r <= row_stop; r++) {
    for(int c = col_start; c <= col_stop; c++) {
      int widx = r*_cols+c;
      if ( wordModified( widx ) ) {
	paint.setPen(qApp->palette().link().color());
	paint.drawText( _wordBBox[widx].left() + wordSpacing()/2,
			_wordBBox[widx].bottom(),
			text.mid(widx*charsPerWord(),charsPerWord()) );
	paint.setPen(qApp->palette().foreground().color());
      } else {
	paint.drawText( _wordBBox[widx].left() + wordSpacing()/2,
			_wordBBox[widx].bottom(),
			text.mid(widx*charsPerWord(),charsPerWord()) );
      }
    }
  }
}
