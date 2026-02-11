keyPressEvent( QKeyEvent *e )
{
    if ( e->key() == Qt::Key_Space )
    {
        switch ( d_data->itemMode )
        {
            case QwtLegend::ClickableItem:
            {
                if ( !e->isAutoRepeat() )
                    setDown( true );
                return;
            }
            case QwtLegend::CheckableItem:
            {
                if ( !e->isAutoRepeat() )
                    setDown( !isDown() );
                return;
            }
            default:;
        }
    }

    QwtTextLabel::keyPressEvent( e );
}
