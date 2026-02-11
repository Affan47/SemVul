drawButton( QPainter* p )
{
  p->fillRect( 0,0, width(), height(), QBrush(QColorGroup(palette()).brush(QPalette::Background)) );
#if 1

  icon().paint( p, rect() );
#else
  p->drawPixmap( (width() - pixmap()->width()) / 2, (height() - pixmap()->height()) / 2, *pixmap() );
#endif
  if ( moveMouse && !isDown() ){
    p->setPen( Qt::white );
    p->drawLine( 0, height() - 1, 0, 0 );
    p->drawLine( 0, 0, width() -1 , 0 );

    p->setPen( QColorGroup(palette()).dark() );
    p->drawLine( width() -1, 0, width() - 1, height() - 1 );
    p->drawLine( width() - 1, height() - 1, 0, height() - 1 );
  }
  if ( isChecked() || isDown() ){
    p->setPen( QColorGroup(palette()).dark() );
    p->drawLine(0 , height() - 1, 0, 0);
    p->drawLine(0, 0, width() -1 , 0);

    p->setPen( Qt::white );
    p->drawLine(width() - 1, height() - 1, 0, height() - 1);
  }
}
