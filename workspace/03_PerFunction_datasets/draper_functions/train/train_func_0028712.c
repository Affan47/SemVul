setColor( const QColor &color)
{
     Q3ColorDrag tmp(color, 0, 0);
     setEncodedData(tmp.encodedData(color_mime_string));

     QPixmap colorpix( 25, 20);
     colorpix.fill( color);
     QPainter p( &colorpix );
     p.setPen( Qt::black );
     p.drawRect(0,0,25,20);
     p.end();
     setPixmap(colorpix, QPoint(-5,-7));
}
