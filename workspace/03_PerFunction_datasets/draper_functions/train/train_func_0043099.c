rowBox( QWidget *w, QPoint *idx ) const
{
    QBoxLayout *box = 0;
    int col;
    for( uint row = 0; row < rows(); ++row )
    {
        box = qobject_cast<QBoxLayout*>( layout()->itemAt( row )->layout() );
        if ( box && ( col = box->indexOf( w ) ) > -1 )
        {
            if ( idx )
            {
                idx->setX( col );
                idx->setY( row );
            }
            return box;
        }
    }
    return NULL;
}
