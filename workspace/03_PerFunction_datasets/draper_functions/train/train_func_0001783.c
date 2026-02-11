paintEvent( QPaintEvent *ev )
{

    QToolBar::paintEvent( ev );


    QPainter p( this );
    Skip *left = &m_prev;
    Skip *right = &m_next;

    if( layoutDirection() == Qt::RightToLeft )
    {
        left = &m_next;
        right = &m_prev;
    }

    if( left->key )
        p.drawPixmap( left->rect.left() + skipMargin,
                      left->rect.y() + ( left->rect.height() - m_skip_left.height() ) /2,
                      m_skip_left );
    if( right->key )
        p.drawPixmap( right->rect.right() - ( m_skip_right.width() + skipMargin ),
                      right->rect.y() + ( right->rect.height() - m_skip_right.height() ) /2,
                      m_skip_right );
    p.end();
}
