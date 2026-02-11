extend_range_for_styles( int *startpos, int *endpos ) {
  IS_UTF8_ALIGNED2(buffer(), (*startpos))
  IS_UTF8_ALIGNED2(buffer(), (*endpos))

  Fl_Text_Selection * sel = mStyleBuffer->primary_selection();
  int extended = 0;


  if ( sel->selected() ) {
    if ( sel->start() < *startpos ) {
      *startpos = sel->start();

      *startpos = buffer()->utf8_align(*startpos);
      IS_UTF8_ALIGNED2(buffer(), (*startpos))
      extended = 1;
    }
    if ( sel->end() > *endpos ) {
      *endpos = sel->end();
      *endpos = buffer()->utf8_align(*endpos);
      IS_UTF8_ALIGNED2(buffer(), (*endpos))
      extended = 1;
    }
  }


  if ( extended )
    *endpos = mBuffer->line_end( *endpos ) + 1;

  IS_UTF8_ALIGNED2(buffer(), (*endpos))
}
