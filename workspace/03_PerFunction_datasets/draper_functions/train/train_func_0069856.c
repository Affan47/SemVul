paintFrameSetRules( QPainter *paint, const QRect& damageRect )
{
  Q_UNUSED( damageRect );
  KHTMLView *view = canvas()->view();
  if (view && !noResize()) {
      paint->setPen( Qt::gray );
      paint->setBrush( Qt::gray );
      const int rBord = 3;
      int sw = element()->border();


      (void) rBord;
      (void) sw;
  }

}
