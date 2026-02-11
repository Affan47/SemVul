constraintsChanged()
{
    if ( !scene() || !scene()->itemDelegate() ) return;
    const Span bs = scene()->itemDelegate()->itemBoundingSpan( getStyleOption(), index() );
    const QRectF br = boundingRect();
    setBoundingRect( QRectF( bs.start(), 0., bs.length(), br.height() ) );
}
