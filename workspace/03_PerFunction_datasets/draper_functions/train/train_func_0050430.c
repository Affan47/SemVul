render( QPainter *painter,
    const QRectF &viewBox, const QRectF &rect ) const
{
    if ( !viewBox.isValid() )
        return;

    QRectF r = rect;

    if ( QwtPainter::roundingAlignment( painter ) )
    {
        r.setLeft ( qRound( r.left() ) );
        r.setRight ( qRound( r.right() ) );
        r.setTop ( qRound( r.top() ) );
        r.setBottom ( qRound( r.bottom() ) );
    }

    d_data->renderer.setViewBox( viewBox );
    d_data->renderer.render( painter, r );
}
